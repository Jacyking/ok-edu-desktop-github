#include "framepdf.h"


namespace office {


FramePDF::FramePDF(QWidget *parent) :
    FrameWidget(parent),
    pdfMgr_(nullptr),
    reader_(nullptr)
{
    DEBUG_LOG_S(L_INFO);
    //PDF PDFIumReaderMgr
    pdfMgr_ = office::pdf::PDFIumReaderMgr::Instance();
    renderer_ = std::make_unique<QLabel>(this);;

}

FramePDF::~FramePDF()
{
    DEBUG_LOG_S(L_INFO);
}

void FramePDF::play(const QFile &filename_)
{

    reader_ = pdfMgr_->LoadPDF(filename_.fileName().toStdString().c_str());
    DEBUG_LOG_S(L_INFO) << " reader:" << reader_;


    int pageCount = reader_->GetPageCount();
    if(pageCount <= 0){
        DEBUG_LOG_S(L_ERROR) << "page count:" << reader_->GetPageCount();
        return;
    }

    QByteArray* byteArray = new QByteArray();

    //载入第一页
    int page = 0;
    bool get = reader_->GetPdfPage(0, byteArray);
    if(!get){
        DEBUG_LOG_S(L_INFO) << "Can not be load Page:" << page;
        return;
    }

    //图片
    bool bRet = false;
    QPixmap pixmap;
    bRet = pixmap.loadFromData((const uchar*)byteArray->data(),byteArray->size() );    //导入方式2
    DEBUG_LOG_S(L_INFO) <<"LoadFromData:"<<bRet;
    if(!bRet){
        return;
    }

    renderer_ = std::make_unique<QLabel>(this);
    renderer_->setPixmap(pixmap);
    renderer_->move(0, 0);
}

}
