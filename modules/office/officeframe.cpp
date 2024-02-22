#include "officeframe.h"
#include "framefactory.h"
#include "framepdf.h"

#include <base/logs.h>
#include <QPixmap>

#include <UI/window/widgetfactory.h>
#include <UI/window/window/VideoPlayer.h>

namespace office
{

    FrameWidget *OfficeFrame::CreateFrame(const backend::FileResult &urlInfo, QWidget *parent)
    {
        DEBUG_LOG_S(L_INFO) << "url:" << urlInfo.url;

        base::FileContentType contentType_ = base::Files::toContentTypeE(urlInfo.contentType);

        DEBUG_LOG_S(L_INFO) << "contentType:" << (int)contentType_;

        FrameWidget *fv = nullptr;

        switch (contentType_)
        {
        case FileContentType::PDF:
        {
            fv = FrameFactory::Create<FramePDF>(parent);
            break;
        }
        case FileContentType::VIDEO:
        {
            //        VideoPlayer* player = new VideoPlayer(parent);
            //        player->setSource(QUrl(urlInfo.url));
            //        player->play();
            //        player->resize(800, 600);

            return nullptr;
        }
        case FileContentType::DOC:
        case FileContentType::DOCX:
        {
            //        axWidget_ = std::make_unique<QAxWidget>("Word.Application", this, Qt::MSWindowsOwnDC);

            //        axWidget_->setProperty("Visible", false);
            //        axWidget_->setProperty("DisplayAlerts", false);

            //        QAxObject* _documents = axWidget_->querySubObject("Documents");
            //        if(!_documents){
            //            DEBUG_LOG_S(L_ERROR) << "documents is nullptr!";
            //            return;
            //        }
            //        QAxObject* _document = _documents->querySubObject("Open(const QString&, bool)", filename, true);
            //        if(!_document)
            //        {
            //            DEBUG_LOG_S(L_ERROR) << "document:" << filename <<" is nullptr!";
            //            return;
            //        }
            //        QAxObject* _words = _document->querySubObject("Words");
            //        if(!_words){
            //            DEBUG_LOG_S(L_ERROR) << "_words:" << filename <<" is nullptr!";
            //            return;
            //        }
            //        int count = _words->dynamicCall("Count()").toInt();
            //        DEBUG_LOG_S(L_INFO) << "word count:" << count;

            ////        for (int a = 1; a <= countWord; a++){
            ////            DEBUG_LOG_S(L_INFO) << _words->querySubObject("Item(int)", a)->dynamicCall("Text()").toString();
            ////        }

            //        QAxObject *pRange = _document->querySubObject("Range()");
            //        if(!pRange){
            //            DEBUG_LOG_S(L_INFO) << "Range() is nullptr!";
            //            return;
            //        }

            //        QVariant wholestory = pRange->dynamicCall("WholeStory()");
            //        QString text = pRange->property("Text").toString();
            //        DEBUG_LOG_S(L_INFO) << "text" << text;

            ////        axWidget_->dynamicCall("SetVisible (bool Visible)", "false");//不显示窗体
            //        axWidget_->setControl(filename);
            break;
        }
        case FileContentType::PPT:
        case FileContentType::PPTX:
        {
            //        axWidget_ = std::make_unique<QAxWidget>("Powerpoint.Application", this, Qt::MSWindowsOwnDC);

            //        QAxObject *presentations = axWidget_->querySubObject( "Presentations" );

            //        presentations->dynamicCall("Open(QString)",filename);
            break;
        }
        case FileContentType::TXT:
        {

            break;
        }
        default:
            //文件不支持。
            break;
        }

        //    if(axWidget_){
        //        axWidget_-> setGeometry (QRect (10, 10, this->width()-10, this->height()-10));
        //        axWidget_->show();
        //        axWidget_->dynamicCall("Quit(void)");
        //    }

        if (fv)
        {
            fv->play(urlInfo.url);
        }
        return fv;
    }

}
