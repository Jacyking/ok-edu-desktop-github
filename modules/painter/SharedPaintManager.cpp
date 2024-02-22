#include "SharedPaintManager.h"
#include "SharedPaintCommandManager.h"
#include "painterevent.h"
#include "PainterWidgetProxy.h"

#include "lib/smartboard/smartboarddraw.h"
#include "lib/smartboard/smartboarddrawline.h"
#include "lib/smartboard/smartboarddrawmove.h"
#include "lib/smartboard/smartboarddrawremove.h"
#include "lib/smartboard/smartboarddrawtext.h"
#include <QBuffer>

#include <base/logs.h>
#include <base/utils.h>

#include <UI/dialog/VideoPlayerDialog.h>

#include <UI/window/window/VideoPlayer.h>

#include "UI/component/OPlayerWidget.h"

#define START_SERVER_PORT 4001
#define DEFAULT_BROADCAST_PORT 3336
#define DEFAULT_BROADCAST_UDP_PORT_FOR_TEXTMSG 3338
#define START_UDP_LISTEN_PORT 5001
#define START_UDP_LISTEN_PORT_FOR_STREAM 6000

#define TIMEOUT_SYNC_MSEC 5000

namespace painter
{

    static int margin = 5;

    class ISharedPaintEvent;

    CSharedPaintManager::CSharedPaintManager(QWidget *painter) : painter_(painter),
                                                                 enabled_(true),
                                                                 syncStartedFlag_(false),
                                                                 commandMngr_(nullptr),
                                                                 listenTcpPort_(-1),
                                                                 listenUdpPort_(-1),
                                                                 retryServerReconnectCount_(0),
                                                                 lastConnectMode_(INIT_MODE),
                                                                 lastConnectPort_(-1),
                                                                 findingServerMode_(false),
                                                                 lastWindowWidth_(0),
                                                                 lastWindowHeight_(0),
                                                                 lastCanvasWidth_(0),
                                                                 lastCanvasHeight_(0),
                                                                 lastScrollHPos_(-1),
                                                                 lastScrollVPos_(-1),
                                                                 gridLineSize_(0),
                                                                 lastPacketId_(-1),
                                                                 backgroundColor_(Qt::white), //默认背景颜色
                                                                 m_networkManager(std::make_unique<network::NetworkHttp>(this))
    {
        DEBUG_LOG_S(L_INFO) << "begin";

        //命令管理器
        commandMngr_ = std::make_shared<CSharedPaintCommandManager>(this);

        //画板事件
        painterEvent_ = std::make_shared<PainterEvent>();

        QRect rect = QRect(margin, margin, painter_->width() - margin * 2, painter_->height() - margin * 2);

        // CSharedPainterScene
        _scene = std::make_shared<CSharedPainterScene>(painterEvent_.get());
        _scene->setCommandMgr(commandMngr_);
        _scene->setSceneRect(rect);
        //    _scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        //    _scene->setStickyFocus(true);

        auto palette = _scene->palette();
        palette.setColor(QPalette::Window, QColor(0, 0, 0, 100));
        _scene->setPalette(palette);

        // QGraphicsView

        _view = std::make_unique<QGraphicsView>(_scene.get(), painter_);
        _view->setRenderHint(QPainter::Antialiasing);
        _view->setCacheMode(QGraphicsView::CacheBackground);
        _view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        _view->setDragMode(QGraphicsView::ScrollHandDrag);
        _view->setFocusPolicy(Qt::ClickFocus);

        //_view->setAutoFillBackground(true);
        //    _view->setAttribute(Qt::WA_TranslucentBackground, true);
        //    _view->setStyleSheet("border:1px solid red");

        _view->show();

        //画板渲染器
        painterRenderer_ = std::make_shared<PainterRenderer>();
        painterRenderer_->setSharedPainterScene(_scene.get());

        myUserInfo_ = std::shared_ptr<CPaintUser>(new CPaintUser(true));

        //画板数据分发
        painterDispatcher_ = std::make_shared<PainterDispatcher>();

        registerObserver(painterDispatcher_.get());
        registerObserver(painterRenderer_.get());

        painterEvent_->setManager(this);



        //接收事件
        connect(_scene.get(), SIGNAL(receivedDropFile(QString)),
                this, SLOT(onReceivedDropFile(QString)));

        connect(_scene.get(), SIGNAL(receivedScreenCapture(QPixmap)),
                this, SLOT(onReceivedScreenCapture(QPixmap)));

        DEBUG_LOG_S(L_INFO) << "end";
    }

    CSharedPaintManager::~CSharedPaintManager(void)
    {
        stopServer();
        close();
        stopListenBroadCast();
    }

    void CSharedPaintManager::initialize(const std::string &myId)
    {
        struct SPaintUserInfoData data;
        data.userId = myId;
        myUserInfo_->setData(data);
    }

    void CSharedPaintManager::openDialog()
    {
    }

    void CSharedPaintManager::setToolType(ToolboxType toolboxType)
    {
        _scene->setToolType(toolboxType);
    }

    void CSharedPaintManager::setSize(const QSize &size)
    {
        _view->resize(size);

        QRect rect = QRect(margin, margin, painter_->width() - margin * 2, painter_->height() - margin * 2);
        _scene->setSceneRect(rect);
    }

    void CSharedPaintManager::onTimeoutSyncStart(void)
    {
        if (syncStartedFlag_ == false)
            close();
    }

    void CSharedPaintManager::onDraw(SmartBoard::SmartBoardDraw *draw)
    {
        if (!draw)
        {
            return;
        }

        DEBUG_LOG_S(L_DEBUG) << "id:" << qstring(draw->id());

        const SmartBoard::DrawLine *line =
            draw->findPlugin<SmartBoard::DrawLine>(SmartBoard::DrawType::Line);
        if (line)
        {
            doLine(draw, line);
            return;
        }

        const SmartBoard::DrawMove *move =
            draw->findPlugin<SmartBoard::DrawMove>(SmartBoard::DrawType::Move);
        if (move)
        {
            doMove(draw, move);
            return;
        }

        const SmartBoard::DrawRemove *remove = draw->findPlugin<SmartBoard::DrawRemove>(SmartBoard::DrawType::Remove);
        if (remove)
        {
            doRemove(draw, remove);
        }

        const SmartBoard::DrawFile *file = draw->findPlugin<SmartBoard::DrawFile>(SmartBoard::DrawType::File);
        if (file)
        {
            doFile(draw, file);
            return;
        }

        const SmartBoard::DrawText *text = draw->findPlugin<SmartBoard::DrawText>(SmartBoard::DrawType::Text);
        if (text)
        {
            doText(draw, text);
            return;
        }
    }

    void CSharedPaintManager::doText(SmartBoard::SmartBoardDraw *draw, const SmartBoard::DrawText *text)
    {
        DEBUG_LOG_S(L_DEBUG) << "text:" << text;

        std::shared_ptr<CTextItem> _item = std::make_shared<CTextItem>("");
        _item->deserialize(std::shared_ptr<SmartBoard::SmartBoardDraw>(draw));

        CPaintItem::Action act = _item->action();
        switch (act)
        {
        case CPaintItem::Action::Create:
        {
            auto y = commandMngr_->addHistoryItem(_item);
            if (y)
            {
                _item->setCanvas(_scene.get());
                _item->draw();
            }
            break;
        }
        case CPaintItem::Action::Update:
        {
            std::shared_ptr<CPaintItem> _uItem = commandMngr_->findItem("", _item->itemId());
            if (_uItem)
            {
                std::static_pointer_cast<CTextItem>(_uItem)->setText(_item->text());
                _uItem->update();
            }
            break;
        }
        }
    }

    void CSharedPaintManager::doFile(SmartBoard::SmartBoardDraw *draw, const SmartBoard::DrawFile *file)
    {
        DEBUG_LOG_S(L_DEBUG) << "file:" << file;

        std::shared_ptr<CFileItem> _item = std::make_shared<CFileItem>("");
        _item->deserialize(std::shared_ptr<SmartBoard::SmartBoardDraw>(draw));

        auto y = commandMngr_->addHistoryItem(_item);
        if (!y)
            return;

        _item->setCanvas(_scene.get());
        _item->draw();
    }

    void CSharedPaintManager::doMove(SmartBoard::SmartBoardDraw *draw, const SmartBoard::DrawMove *move)
    {

        DEBUG_LOG_S(L_DEBUG) << "move:" << move;

        std::shared_ptr<CPaintItem> _item = commandMngr_->findItem("", move->moveId());
        if (!_item)
        {
            DEBUG_LOG_S(L_ERROR) << "moveId:" << qstring(move->moveId()) << " is not exist!";
            return;
        }

        _item->move(move->position().x, move->position().y);
    }

    void CSharedPaintManager::doRemove(SmartBoard::SmartBoardDraw *draw,
                                       const SmartBoard::DrawRemove *remove)
    {
        DEBUG_LOG_S(L_DEBUG) << "remove:" << remove;

        std::shared_ptr<CPaintItem> _item = commandMngr_->findItem("", remove->removeId());
        if (!_item)
        {
            DEBUG_LOG_S(L_ERROR) << "remove:" << qstring(remove->removeId()) << " is not exist!";
            return;
        }

        _scene->removePaintItem(_item.get());
    }

    void CSharedPaintManager::doLine(SmartBoard::SmartBoardDraw *draw, const SmartBoard::DrawLine *line)
    {
        DEBUG_LOG_S(L_DEBUG) << "line:" << line;
        std::shared_ptr<CLineItem> _item = std::make_shared<CLineItem>("");
        _item->deserialize(std::shared_ptr<SmartBoard::SmartBoardDraw>(draw));

        auto y = commandMngr_->addHistoryItem(_item);
        if (!y)
            return;

        _item->setCanvas(_scene.get());
        _item->draw();
    }

    bool CSharedPaintManager::addPaintItem(std::shared_ptr<CPaintItem> item)
    {
        if (!enabled_)
            return false;

        item->setOwner("");
        auto y = commandMngr_->addHistoryItem(item);
        if (y)
        {
            std::shared_ptr<CAddItemCommand> command = std::make_shared<CAddItemCommand>(item);
            y = commandMngr_->executeCommand(command);
        }

        return y;
    }

    bool CSharedPaintManager::startListenBroadCast(void)
    {

        return true;
    }

    bool CSharedPaintManager::startFindingServer(void)
    {
        stopListenBroadCast();
        _stopFindingServer();
        return true;
    }

    bool CSharedPaintManager::startServer(int port)
    {

        return true;
    }

    void CSharedPaintManager::stopListenBroadCast(void)
    {
        qDebug() << "stopListenBroadCast";
    }

    void CSharedPaintManager::_stopFindingServer(void)
    {
        qDebug() << "_stopFindingServer" << findingServerMode_;

        if (!findingServerMode_)
            return;

        findingServerMode_ = false;
    }

    void CSharedPaintManager::stopFindingServer(void)
    {
    }

    void CSharedPaintManager::stopServer(void)
    {
    }

    bool CSharedPaintManager::deserializeData(const char *data, size_t size)
    {

        return true;
    }

    std::string CSharedPaintManager::serializeData(const std::string *target)
    {
        std::string allData;

        return allData;
    }

    void CSharedPaintManager::clearAllItems()
    // this function must be called on main thread!
    {
        qDebug() << "CSharedPaintManager::clearAllItems()";

        backgroundColor_ = Qt::white;
        backgroundImageItem_ = std::shared_ptr<CBackgroundImageItem>();

        _scene->clearScreen();

        // all data clear
        if (commandMngr_)
            commandMngr_->clear();

        // history must be removed with removing all paint item.
        //		clearAllHistoryUsers();
    }
    void CSharedPaintManager::toDrawQueue(SmartBoard::SmartBoardDraw *draw)
    {
        onDraw(draw);
    }

    void CSharedPaintManager::onReceivedDropFile(QString path)
    {
        DEBUG_LOG_S(L_INFO) << path;

        QFile *file = new QFile(path);
        if (!file || !file->exists())
        {
            DEBUG_LOG_S(L_ERROR) << "file is not exist!";
            return;
        }

//        m_networkManager->upload(file, [this](QJsonObject &result)
//                                {
//        //解析返回的数据
//        backend::FileResult _dr = network::NetworkHttp::parseDownloadResult(result);
//        if(!_dr.success){
//            DEBUG_LOG_S(L_ERROR) << "Upload error!";
//        }
//        //添加到视图
//        _scene->addGeneralUrlItem(QPointF(0, 0), _dr); });
    }

    /** Receive screen capture image
     * @brief CSharedPaintManager::onReceivedScreenCapture
     * @param pixmap
     */
    void CSharedPaintManager::onReceivedScreenCapture(QPixmap pixmap)
    {
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");

        QString timestamp = base::Utils::GetTimestamp();

        QString filename = qsl("ScreenCapture_%1").arg(timestamp);
        QString contentType = "image/png";

//        network::ByteInfo byteInfo = {ba, filename, contentType};

//        m_networkManager->GetURL(byteInfo, [this](QJsonObject &result)
//                                {
//        //解析返回的数据
//        backend::FileResult _dr = network::NetworkHttp::parseDownloadResult(result);
//        if(!_dr.success){
//            DEBUG_LOG_S(L_ERROR) << "Upload error!";
//        }
        //添加到视图
//        _scene->addGeneralUrlItem(QPointF(0, 0), _dr); });
    }

}
