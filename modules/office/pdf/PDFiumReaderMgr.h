#pragma once

#include <QByteArray>
#include <iostream>
#include <map>

namespace office {
namespace pdf {

class PDFIumReader;

typedef std::map<std::string, PDFIumReader*> PDFReaders;

class PDFIumReaderMgr
{
public:
    static PDFIumReaderMgr *Instance();
    PDFIumReader * LoadPDF(const char *name);
    void ClosePDF(PDFIumReader *reader);
//    char *LoadPage(const char* filename, int page, float& width, float& height,  bool OutBmp);
//    int  GetPageCount(const char* filename);
//    QByteArray* GetNextPage(const char* filename, int &page, float& width, float& height, bool OutBmp);
//    void SetCurrentPage(const char* filename, int page);

private:
    PDFIumReaderMgr(){}
    ~PDFIumReaderMgr(){}

public:
    PDFReaders m_pdfReaders;
};


}
}
