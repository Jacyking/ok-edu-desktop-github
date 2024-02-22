#pragma once

#if defined PDF_ENABLE_SKIA && !defined _SKIA_SUPPORT_
#define _SKIA_SUPPORT_
#endif

#include <limits.h>
//#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <pdfium/public/cpp/fpdf_scopers.h>
#include <pdfium/public/fpdf_annot.h>
#include <pdfium/public/fpdf_attachment.h>
#include <pdfium/public/fpdf_dataavail.h>
#include <pdfium/public/fpdf_edit.h>
#include <pdfium/public/fpdf_ext.h>
#include <pdfium/public/fpdf_formfill.h>
#include <pdfium/public/fpdf_progressive.h>
#include <pdfium/public/fpdf_structtree.h>
#include <pdfium/public/fpdf_text.h>
#include <pdfium/public/fpdfview.h>

#include "PDFiumReader.h"

// #include "pdfium_test_dump_helper.h"
// #include "pdfium_test_event_helper.h"
// #include "pdfium_test_write_helper.h"

#include <stdlib.h>

namespace pdfium {

// Used with std::unique_ptr to free() objects that can't be deleted.
struct FreeDeleter {
  inline void operator()(void* ptr) const { free(ptr); }
};

}
namespace office {
namespace pdf {

#ifdef _WIN32
#define access _access

#define R_OK 4
#endif

enum OutputFormat {
    OUTPUT_NONE,
    OUTPUT_PAGEINFO,
    OUTPUT_STRUCTURE,
    OUTPUT_TEXT,
    OUTPUT_PPM,
    OUTPUT_PNG,
    OUTPUT_ANNOT,
#ifdef _WIN32
    OUTPUT_BMP,
    OUTPUT_EMF,
    OUTPUT_PS2,
    OUTPUT_PS3,
#endif
#ifdef PDF_ENABLE_SKIA
    OUTPUT_SKP,
#endif
};

struct Options {
    Options() = default;

    bool show_config = false;
    bool show_metadata = false;
    bool send_events = false;
    bool render_oneshot = false;
    bool save_attachments = false;
    bool save_images = false;
#ifdef PDF_ENABLE_V8
    bool disable_javascript = false;
#ifdef PDF_ENABLE_XFA
    bool disable_xfa = false;
#endif  // PDF_ENABLE_XFA
#endif  // PDF_ENABLE_V8
    bool pages = false;
    bool md5 = false;
#ifdef ENABLE_CALLGRIND
    bool callgrind_delimiters = false;
#endif  // ENABLE_CALLGRIND
    OutputFormat output_format = OUTPUT_NONE;
    std::string scale_factor_as_string;
    std::string exe_path;
    std::string bin_directory;
    std::string font_directory;
    int first_page = 0;  // First 0-based page number to renderer.
    int last_page = 0;   // Last 0-based page number to renderer.
    time_t time = -1;
};

struct FPDF_FORMFILLINFO_PDFiumTest final : public FPDF_FORMFILLINFO {
    // Hold a map of the currently loaded pages in order to avoid them
    // to get loaded twice.
    std::map<int, ScopedFPDFPage> loaded_pages;

    // Hold a pointer of FPDF_FORMHANDLE so that PDFium app hooks can
    // make use of it.
    FPDF_FORMHANDLE form_handle;
};



class PDFIumLoader {
public:
    PDFIumLoader(){}
    PDFIumLoader(const char* pBuf, size_t len);
    const char* m_pBuf;
    size_t m_Len;
};

class PDFIumReader
{
private:
    //    static void WritePpm(const char* pdf_name, int num, const char* buffer, int stride, int width, int height);
//    static void AddSegment(FX_DOWNLOADHINTS* pThis, size_t offset, size_t size);
//    static bool IsDataAvail(FX_FILEAVAIL* pThis, size_t offset, size_t size);
//    static int  GetBlock(void* param, unsigned long pos, unsigned char* pBuf, unsigned long size);
//    static int  FormAlert(IPDF_JSPLATFORM*, FPDF_WIDESTRING, FPDF_WIDESTRING, int, int);

public:
    PDFIumReader();
    virtual ~PDFIumReader();

    bool Reader(const std::string& name);
    void Close();



    int GetPageCount(){return m_nPageCount;}

    bool GetPdfPage(int pageIndex, QByteArray* byteArray);

    bool GetNextPage(QByteArray* byteArray);
    bool GetPrevPage(QByteArray* byteArray);

    void SetCurrentPage(int pageIndex);

    virtual const std::string& fileName() const {
        return m_strFileName;
    }

private:
    bool RenderPage(
                        FPDF_DOCUMENT doc,
                        FPDF_FORMHANDLE form,
                        FPDF_FORMFILLINFO_PDFiumTest* form_fill_info,
                        const int page_index,
                        const Options& options,
                        const std::string& events,

                        QByteArray * outBuf
                    );

    bool RenderPdf(const std::string& name,
                   const char* pBuf,
                   size_t len,
                   const Options& options,
                   const std::string& events);

    std::string events_;
    Options options_;

    std::unique_ptr<FPDF_FILEACCESS> file_access;
    std::unique_ptr<FX_FILEAVAIL> file_avail;
    std::unique_ptr<FX_DOWNLOADHINTS> hints;

    std::unique_ptr<PDFIumLoader> loader_;

    size_t file_length;

    std::unique_ptr<char, pdfium::FreeDeleter> file_contents;

    ScopedFPDFAvail pdf_avail_;
    ScopedFPDFDocument doc_;
    ScopedFPDFFormHandle form_;

    FPDF_FORMFILLINFO_PDFiumTest form_callbacks;
    //    FPDF_DOCUMENT m_pPdfDoc = nullptr;
//    FPDF_FORMFILLINFO m_formCallbacks;
//    IPDF_JSPLATFORM m_platformcallbacks;
//    FPDF_FORMHANDLE m_formHandle;
//    FX_DOWNLOADHINTS m_hints;
//    FX_FILEAVAIL m_fileAvail;
//    FPDF_FILEACCESS m_fileAccess;
    PDFIumLoader m_PDFIumLoader;
    //    FPDF_AVAIL m_PdfAvail;
    //    char *m_pdfBuf;
//    bool m_bIsLinearized = false;
    std::string m_strFileName;

    int m_nPageCount = 0;
    int m_nCurrentPage = 0;

    int rendered_pages = 0;
    int bad_pages = 0;

    bool bIsLinearized_ = false;
    bool bCanLoad = false;

};


}
}

