#include "PainterView.h"

#include <memory>

#include <QClipboard>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMimeData>
#include <QString>
#include <QTextEdit>
#include <QWidget>

#include "lib/smartboard/smartboardcontroller.h"
#include "lib/smartboard/smartboardcontrollerselect.h"
#include "lib/smartboard/smartboardcontrollervoice.h"
#include "lib/smartboard/smartboarddraw.h"

#include "PaintItem.h"
#include "SharedPaintManager.h"
#include "SharedPainterScene.h"

#include "PainterMdiArea.h"
#include "base/r.h"

#include <base/logs.h>
#include <base/timer.h>
#include <base/utils.h>

#include "lib/messenger/messenger.h"
// #include <office/framepdf.h>
// #include <office/framefactory.h>
// #include <office/officeframe.h>

#include "OPainterToolBox.h"
#include "OVideoViewport.h"
#include "PageClassing.h"
#include "UI/component/OPlayerWidget.h"
#include <UI/WindowManager.h>
#include <UI/window/window/VideoPlayer.h>

namespace painter {

PainterView::PainterView(QWidget *parent) : QWidget(parent) {
  DEBUG_LOG(("begin"));
  setObjectName("PainterView");

  setAutoFillBackground(true);
  QPalette p = palette();
  p.setBrush(QPalette::Window, QColor("#123456"));
  setPalette(p);

  //  networkManager_ = network::NetworkManager::Get();

  // Painter Manager
  painterManager_ = std::make_unique<CSharedPaintManager>(this);

  connect(painterManager_->scene().get(), &CSharedPainterScene::openFile, this,
          &PainterView::onOpenFile);

  //  auto im = lib::IM::Messenger::getInstance()->im();

  // IMSmartBord
  //  _imSmartBoard = im->getSmartBoard();

  //  connect(_imSmartBoard, &smartboard::IMSmartBoard::receivedDraw, this,
  //          &Painter::onReceivedDraw);

  //  connect(_imSmartBoard, SIGNAL(pubsubEvent(gloox::PubSub::ItemList &)),
  //  this,
  //          SLOT(onPubSubEvent(gloox::PubSub::ItemList &)));

  mdiArea = new PainterMdiArea(painterManager_->scene(), this);

  // 工具箱
  _oToolbox = std::make_unique<OPainterToolBox>(this);
  _oToolbox->move(this->width() - _oToolbox->width() - 20, 20);

  // 连接工具箱和画板之间的信号
  connect(_oToolbox.get(), &OPainterToolBox::toolChange, //
          this, &PainterView::onToolBoxChanged);

  // text tool
  connect(_oToolbox.get(), &OPainterToolBox::textColorChange, this,
          &PainterView::setTextColor);
  connect(_oToolbox.get(), &OPainterToolBox::textWeightChange, this,
          &PainterView::setTextWeight);

  // pen tool
  connect(_oToolbox.get(), &OPainterToolBox::penColorChange, this,
          &PainterView::setPenColor);
  connect(_oToolbox.get(), &OPainterToolBox::penWeightChange, this,
          &PainterView::setPenWeight);

  // 控制按钮
  _oController = std::make_unique<WhiteboardController>(this);
  _oController->move(width() - 320, 20);

  connect(_oController.get(), SIGNAL(checked(context::WB::WB_CTRL, bool)),
          SLOT(onCtrollerChecked(context::WB::WB_CTRL, bool)));

  DEBUG_LOG(("end"));
}

PainterView::~PainterView() {}

PainterView *PainterView::Get(QWidget *parent) {
  static PainterView *const painter = new PainterView(parent);
  return painter;
}

void PainterView::showEvent(QShowEvent *event) { Q_UNUSED(event); }

void PainterView::resizeEvent(QResizeEvent *e) {
  //     DEBUG_LOG_S(L_INFO) << "size:" << e->size();

  painterManager_->setSize(e->size());

  _oToolbox->move(this->width() - _oToolbox->width() - 20, 20);

  _oController->move(width() - 320, 20);

#ifndef NO_PAINTER_MDI_AREA
  mdiArea->setFixedSize(e->size());
#endif
}

void PainterView::onReceivedUrlInfo(ok::backend::FileResult _dr) {
  DEBUG_LOG_S(L_INFO) << "file:" << _dr.name;
}

void PainterView::onReceivedDraw(SmartBoard::SmartBoardDraw *draw) {
  painterManager_->toDrawQueue(draw);
}

void PainterView::onOpenFile(std::shared_ptr<CFileItem> file) {
  DEBUG_LOG_S(L_INFO) << "file:" << file->name();
  if (file->name().isEmpty()) {
    return;
  }

  backend::FileResult _dr;
  _dr.url = file->url();
  _dr.name = file->name();
  _dr.contentType = file->contentType();

  // 类型
  base::FileContentType contentType_ =
      base::Files::toContentTypeE(_dr.contentType);

  switch (contentType_) {
  case base::FileContentType::PDF: {
    // auto fv = office::FrameFactory::Create<office::FramePDF>(this);
    // fv->play(_dr.url);
    // fv->move(0, 0);
    // fv->show();

    break;
  }
  case base::FileContentType::VIDEO: {
    auto player = new OPlayerWidget(this);
    player->setSource(QUrl(_dr.url));
    player->play();
    player->resize(800, 600);
    player->show();

#ifndef NO_PAINTER_MDI_AREA
    QPoint pos(0, 0);
    QMdiSubWindow *aSubWin = mdiArea->activeSubWindow();
    if (aSubWin) {
      pos.setX(aSubWin->x() + 20);
      pos.setY(aSubWin->y() + 20);

      if (!mdiArea->rect().contains(pos)) {
        pos.setX(0);
        pos.setY(0);
      }
    }

    QMdiSubWindow *subWin = mdiArea->addSubWindow(player);
    subWin->move(pos);
    subWin->show();
#endif

    break;
  }
  default:

    break;
  }
}

void PainterView::onToolBoxChanged(ToolboxType toolboxType) {
  qDebug() << "onToolBoxChanged" << toolboxType;
  painterManager_->setToolType(toolboxType);
}

void PainterView::setTextColor(QColor clr) {
  // DEBUG_LOG_S(L_INFO) << clr.name();
  painterManager_->scene()->setTextColor(clr);
}

void PainterView::setTextWeight(int weight) {
  int width = 10 + weight * 4;
  // DEBUG_LOG_S(L_INFO) << weight << "width:" << width;
  painterManager_->scene()->setTextWidth(width);
}

void PainterView::setPenColor(QColor clr) {
  // DEBUG_LOG_S(L_INFO) << clr.name();
  painterManager_->scene()->setPenColor(clr);
}

void PainterView::setPenWeight(int weight) {
  int width = weight * 2;
  // DEBUG_LOG_S(L_INFO) << weight << "width:" << width;
  painterManager_->scene()->setPenWidth(width);
}

void PainterView::onCtrollerChecked(WB_CTRL ctrl, bool checked) {
  const UI::page::PageClassing *pclassing =
      UI::WindowManager::Instance()->getPageClassing();
  const OVideoViewport *videoViewport = pclassing->videoViewport();
  const std::list<ok::backendUserJID> checkedUsers =
      videoViewport->isCheckedUsers();

  if (checkedUsers.empty())
    return;

  std::list<std::string> us;

  for (auto e : checkedUsers) {
    us.push_back(e.id.toStdString());
  }

  switch (ctrl) {
  case context::WB::WB_CTRL::MOVE:
    break;
  case context::WB::WB_CTRL::MUTE: {
    std::string id = base::Utils::GetUUID().toStdString();

    SmartBoard::ControllerVoice *voice = new SmartBoard::ControllerVoice(id);

    if (checked) {
      voice->setAction(SmartBoard::Action::OFF);
    } else
      voice->setAction(SmartBoard::Action::ON);

    std::shared_ptr<SmartBoard::Controller> ctl =
        std::make_shared<SmartBoard::Controller>(id);
    ctl->addPlugin(voice);

    SmartBoard::UserList &_t_us =
        const_cast<SmartBoard::UserList &>(ctl->userList());
    std::copy(us.begin(), us.end(), std::back_inserter(_t_us));

    //    _imSmartBoard->sendController(ctl);

    break;
  }
  case context::WB::WB_CTRL::WB:
    break;
  case context::WB::WB_CTRL::RE:

    break;
  case context::WB::WB_CTRL::OK:

    break;
  case context::WB::WB_CTRL::GIFT:

    break;
  case context::WB::WB_CTRL::ALL: {
    std::string id = base::Utils::GetUUID().toStdString();

    SmartBoard::ControllerSelect *select = new SmartBoard::ControllerSelect(id);

    if (checked) {
      select->setAction(SmartBoard::Action::ON);
    } else
      select->setAction(SmartBoard::Action::OFF);

    std::shared_ptr<SmartBoard::Controller> ctl =
        std::make_shared<SmartBoard::Controller>(id);
    ctl->addPlugin(select);

    SmartBoard::UserList &_t_us =
        const_cast<SmartBoard::UserList &>(ctl->userList());
    std::copy(us.begin(), us.end(), std::back_inserter(_t_us));

    //    _imSmartBoard->sendController(ctl);

    break;
  }
  }
}

// void Painter::onPubSubEvent(PubSub::ItemList &items) {
//   DEBUG_LOG(("begin"));
//   for (PubSub::Item *item : items) {
//     DEBUG_LOG(("item id:%1").arg(qstring(item->id())));
//   }
// }

// void Painter::onLogin() {
//   if (networkManager_->userManager()->isTeacher()) {
//     _oController->show();
//   } else {
//     _oController->hide();
//   }
// }
//
// void Painter::onLogout() {}
} // namespace painter
