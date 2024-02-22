#include "PDFiumReaderMgr.h"
#include "PDFiumReader.h"

#include <base/logs.h>

namespace office
{
    namespace pdf
    {

        using namespace std;

        PDFIumReaderMgr *PDFIumReaderMgr::Instance()
        {
            static PDFIumReaderMgr mgr;
            return &mgr;
        }

        PDFIumReader *PDFIumReaderMgr::LoadPDF(const char *name)
        {
            DEBUG_LOG_S(L_INFO) << "name:" << name;
            if (strlen(name) == 0)
            {
                return nullptr;
            }

            if (m_pdfReaders.find(name) != m_pdfReaders.end())
            {
                std::cout << "this file has loaded" << endl;
                return m_pdfReaders.find(name)->second;
            }
            PDFIumReader *reader = new PDFIumReader();
            reader->Reader(name);
            m_pdfReaders[name] = reader;
            return reader;
        }

        void PDFIumReaderMgr::ClosePDF(PDFIumReader *reader)
        {
            if (!reader)
            {
                return;
            }

            const string name = reader->fileName();
            if (m_pdfReaders.find(name) == m_pdfReaders.end())
                return;
            //移除
            m_pdfReaders.erase(name);
            //关闭
            reader->Close();
            delete reader;
        }

        // char * PDFIumReaderMgr::LoadPage(const char* filename,
        //                                  int page,
        //                                  float& width,
        //                                  float& height,
        //                                  bool OutBmp)
        //{
        //     if (m_pdfReaders.find(filename) == m_pdfReaders.end())
        //         return 0;
        //     return m_pdfReaders.find(filename)->second->GetPdfPage(page, width, height, OutBmp);
        // }

        // int PDFIumReaderMgr::GetPageCount(const char* filename)
        //{
        //     if (m_pdfReaders.find(filename) == m_pdfReaders.end())
        //         return 0;
        //     return m_pdfReaders.find(filename)->second->GetPageCount();
        // }

        // QByteArray* PDFIumReaderMgr::GetNextPage(const char* filename, int &page, float& width, float& height, bool OutBmp)
        //{
        //     if (m_pdfReaders.find(filename) == m_pdfReaders.end())
        //         return 0;
        //     return m_pdfReaders.find(filename)->second->GetNextPage();
        // }

        // void PDFIumReaderMgr::SetCurrentPage(const char* filename, int page)
        //{
        //     if (m_pdfReaders.find(filename) == m_pdfReaders.end())
        //         return ;
        //     m_pdfReaders.find(filename)->second->SetCurrentPage(page);
        // }

    }
}
