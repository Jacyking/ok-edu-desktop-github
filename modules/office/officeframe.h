#ifndef OFFICEFRAME_H
#define OFFICEFRAME_H

//#include <QAxWidget>
#include <QLabel>
#include <QWidget>

#include "lib/network/NetworkManager.h"
#include <base/files.h>


#include "pdf/PDFiumReader.h"
#include "pdf/PDFiumReaderMgr.h"

#include "framewidget.h"

namespace office {

class OfficeFrame {

private:
  OfficeFrame();

public:
  static FrameWidget *CreateFrame(const backend::FileResult &url,
                                  QWidget *parent = nullptr);

private:
  //    QString filename_;
  //    base::FileContentType contentType_;
  //    pdf::PDFIumReaderMgr* pdfMgr_;
  //    pdf::PDFIumReader* reader_;

  //    std::unique_ptr<QAxWidget> axWidget_;
  //    std::unique_ptr<QLabel> renderer_;
};

} // namespace office
#endif // OFFICEFRAME_H
