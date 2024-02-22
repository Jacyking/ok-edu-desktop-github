#include "PDFiumReader.h"

#include <pdfium/testing/test_support.h>
#include <pdfium/testing/utils/path_service.h>

#include <base/logs.h>

namespace office
{
    namespace pdf
    {

        using namespace std;

        FPDF_FORMFILLINFO_PDFiumTest *ToPDFiumTestFormFillInfo(
            FPDF_FORMFILLINFO *form_fill_info)
        {
            return static_cast<FPDF_FORMFILLINFO_PDFiumTest *>(form_fill_info);
        }

        FPDF_BOOL Is_Data_Avail(FX_FILEAVAIL *avail, size_t offset, size_t size)
        {
            DEBUG_LOG_S(L_INFO) << "avail:" << avail << " offset:" << offset << " size:" << size;
            return true;
        }

        FPDF_BOOL NeedToPauseNow(IFSDK_PAUSE *p)
        {
            return true;
        }

        void Add_Segment(FX_DOWNLOADHINTS *hints, size_t offset, size_t size)
        {
            DEBUG_LOG_S(L_INFO) << "hints:" << hints << " offset:" << offset << " size:" << size;
        }

        void OutputMD5Hash(const char *file_name, const char *buffer, int len)
        {
            // Get the MD5 hash and write it to stdout.
            std::string hash = GenerateMD5Base16(reinterpret_cast<const uint8_t *>(buffer), len);
            DEBUG_LOG_S(L_INFO) << "file_name:" << file_name << " MD5:" << hash.c_str();
        }

        std::tuple<int, std::string> PrintLastError()
        {

            unsigned long err = FPDF_GetLastError();
            switch (err)
            {
            case FPDF_ERR_SUCCESS:
                return std::make_tuple(err, "Success");
            case FPDF_ERR_UNKNOWN:
                return std::make_tuple(err, "Unknown error");
            case FPDF_ERR_FILE:
                return std::make_tuple(err, "File not found or could not be opened");
            case FPDF_ERR_FORMAT:
                return std::make_tuple(err, "File not in PDF format or corrupted");
            case FPDF_ERR_PASSWORD:
                return std::make_tuple(err, "Password required or incorrect password");
            case FPDF_ERR_SECURITY:
                return std::make_tuple(err, "Unsupported security scheme");
            case FPDF_ERR_PAGE:
                return std::make_tuple(err, "Page not found or content error");
#ifdef PDF_ENABLE_XFA
            case FPDF_ERR_XFALOAD:
                return std::make_tuple(err, "Load XFA error");
            case FPDF_ERR_XFALAYOUT:
                return std::make_tuple(err, "Layout XFA error");
#endif
            }
            return std::make_tuple(err, "Unknown error");
        }

        void ExampleUnsupportedHandler(UNSUPPORT_INFO *, int type)
        {
            std::string feature = "Unknown";
            switch (type)
            {
            case FPDF_UNSP_DOC_XFAFORM:
                feature = "XFA";
                break;
            case FPDF_UNSP_DOC_PORTABLECOLLECTION:
                feature = "Portfolios_Packages";
                break;
            case FPDF_UNSP_DOC_ATTACHMENT:
            case FPDF_UNSP_ANNOT_ATTACHMENT:
                feature = "Attachment";
                break;
            case FPDF_UNSP_DOC_SECURITY:
                feature = "Rights_Management";
                break;
            case FPDF_UNSP_DOC_SHAREDREVIEW:
                feature = "Shared_Review";
                break;
            case FPDF_UNSP_DOC_SHAREDFORM_ACROBAT:
            case FPDF_UNSP_DOC_SHAREDFORM_FILESYSTEM:
            case FPDF_UNSP_DOC_SHAREDFORM_EMAIL:
                feature = "Shared_Form";
                break;
            case FPDF_UNSP_ANNOT_3DANNOT:
                feature = "3D";
                break;
            case FPDF_UNSP_ANNOT_MOVIE:
                feature = "Movie";
                break;
            case FPDF_UNSP_ANNOT_SOUND:
                feature = "Sound";
                break;
            case FPDF_UNSP_ANNOT_SCREEN_MEDIA:
            case FPDF_UNSP_ANNOT_SCREEN_RICHMEDIA:
                feature = "Screen";
                break;
            case FPDF_UNSP_ANNOT_SIG:
                feature = "Digital_Signature";
                break;
            }
            DEBUG_LOG_S(L_INFO) << "Unsupported feature: " << feature.c_str();
        }

        PDFIumReader::PDFIumReader()
        {
            DEBUG_LOG_S(L_INFO) << "begin";
        }

        PDFIumReader::~PDFIumReader()
        {
            DEBUG_LOG_S(L_INFO) << "begin";
            Close();
        }

        FPDF_PAGE GetPageForIndex(FPDF_FORMFILLINFO *param,
                                  FPDF_DOCUMENT doc,
                                  int index)
        {

            DEBUG_LOG_S(L_INFO) << index;

            //    if (bIsLinearized_) {
            //        nRet = PDF_DATA_NOTAVAIL;
            //        while (nRet == PDF_DATA_NOTAVAIL)
            //            nRet = FPDFAvail_IsPageAvail(pdf_avail_.get(), i, &hints);

            //        if (nRet == PDF_DATA_ERROR) {
            //            DEBUG_LOG_S(L_ERROR) << "Unknown error in checking if page " << i << " is available.\n";
            //            return false;
            //        }
            //    }

            FPDF_FORMFILLINFO_PDFiumTest *form_fill_info =
                ToPDFiumTestFormFillInfo(param);

            auto &loaded_pages = form_fill_info->loaded_pages;
            auto iter = loaded_pages.find(index);
            if (iter != loaded_pages.end())
                return iter->second.get();

            ScopedFPDFPage page(FPDF_LoadPage(doc, index));
            if (!page)
                return nullptr;

            // Mark the page as loaded first to prevent infinite recursion.
            FPDF_PAGE page_ptr = page.get();
            loaded_pages[index] = std::move(page);

            FPDF_FORMHANDLE &form_handle = form_fill_info->form_handle;
            FORM_OnAfterLoadPage(page_ptr, form_handle);
            FORM_DoPageAAction(page_ptr, form_handle, FPDFPAGE_AACTION_OPEN);
            return page_ptr;
        }

        bool PDFIumReader::RenderPage(
            FPDF_DOCUMENT doc,
            FPDF_FORMHANDLE form,
            FPDF_FORMFILLINFO_PDFiumTest *form_fill_info,
            const int page_index,
            const Options &options,
            const std::string &events,
            QByteArray *outBuf)
        {

            DEBUG_LOG_S(L_INFO) << "name:" << qstring(m_strFileName)
                                << " doc:" << doc;

            int nRet = PDF_DATA_NOTAVAIL;
            if (bIsLinearized_)
            {
                while (nRet == PDF_DATA_NOTAVAIL)
                    nRet = FPDFAvail_IsPageAvail(pdf_avail_.get(), page_index, hints.get());

                if (nRet == PDF_DATA_ERROR)
                {
                    DEBUG_LOG_S(L_ERROR) << "Unknown error in checking if page " << page_index << " is available.";
                    return false;
                }
            }

            FPDF_PAGE page = GetPageForIndex(form_fill_info, doc, page_index);
            if (!page)
            {
                DEBUG_LOG_S(L_ERROR) << "GetPageForIndex page is nullptr.";
                return false;
            }

            if (options.send_events)
                SendPageEvents(form, page, events);

            //    if (options.save_images)
            //        WriteImages(page, name.c_str(), page_index);

            //    if (options.output_format == OUTPUT_PAGEINFO) {
            //        DumpPageInfo(page, page_index);
            //        return true;
            //    }
            //    if (options.output_format == OUTPUT_STRUCTURE) {
            //        DumpPageStructure(page, page_index);
            //        return true;
            //    }

            //    ScopedFPDFTextPage text_page(FPDFText_LoadPage(page));
            double scale = 1.0;
            if (!options.scale_factor_as_string.empty())
                std::stringstream(options.scale_factor_as_string) >> scale;

            auto width = static_cast<int>(FPDF_GetPageWidth(page) * scale);
            auto height = static_cast<int>(FPDF_GetPageHeight(page) * scale);
            int alpha = FPDFPage_HasTransparency(page) ? 1 : 0;

            ScopedFPDFBitmap bitmap(FPDFBitmap_Create(width, height, alpha));
            if (!bitmap)
            {
                DEBUG_LOG_S(L_ERROR) << "FPDFBitmap_Create error!";
                return false;
            }

            FPDF_DWORD fill_color = alpha ? 0x00000000 : 0xFFFFFFFF;
            FPDFBitmap_FillRect(bitmap.get(), 0, 0, width, height, fill_color);

            if (options.render_oneshot)
            {
                // Note, client programs probably want to use this method instead of the
                // progressive calls. The progressive calls are if you need to pause the
                // rendering to update the UI, the PDF renderer will break when possible.
                FPDF_RenderPageBitmap(bitmap.get(), page, 0, 0, //
                                      width, height, 0, FPDF_ANNOT);
            }
            else
            {
                IFSDK_PAUSE pause;
                pause.version = 1;
                pause.NeedToPauseNow = &NeedToPauseNow;

                int rv = FPDF_RenderPageBitmap_Start(bitmap.get(), page, 0, 0, width,
                                                     height, 0, FPDF_ANNOT, &pause);
                while (rv == FPDF_RENDER_TOBECONTINUED)
                    rv = FPDF_RenderPage_Continue(page, &pause);
            }

            FPDF_FFLDraw(form, bitmap.get(), page, 0, 0, width, height, 0, FPDF_ANNOT);

            if (!options.render_oneshot)
                FPDF_RenderPage_Close(page);

            int stride = FPDFBitmap_GetStride(bitmap.get());

            char *buffer = reinterpret_cast<char *>(FPDFBitmap_GetBuffer(bitmap.get()));

            std::string image_file_name;

            switch (options.output_format)
            {
#ifdef _WIN32
            case OUTPUT_BMP:
            {
                bool writeBmp = WriteBmp(buffer, outBuf, width, height, stride);
                DEBUG_LOG_S(L_INFO) << "writeBmp:" << writeBmp;
            }
            break;

            case OUTPUT_EMF:
                WriteEmf(page, m_strFileName.c_str(), page_index);
                break;

            case OUTPUT_PS2:
            case OUTPUT_PS3:
                WritePS(page, m_strFileName.c_str(), page_index);
                break;
#endif
            case OUTPUT_TEXT:
                WriteText(page, m_strFileName.c_str(), page_index);
                break;

            case OUTPUT_ANNOT:
                WriteAnnot(page, m_strFileName.c_str(), page_index);
                break;

            case OUTPUT_PNG:
                image_file_name =
                    WritePng(m_strFileName.c_str(), page_index, buffer, stride, width, height);
                break;

            case OUTPUT_PPM:
                image_file_name =
                    WritePpm(m_strFileName.c_str(), page_index, buffer, stride, width, height);
                break;

#ifdef PDF_ENABLE_SKIA
            case OUTPUT_SKP:
            {
                std::unique_ptr<SkPictureRecorder> recorder(
                    reinterpret_cast<SkPictureRecorder *>(
                        FPDF_RenderPageSkp(page, width, height)));
                FPDF_FFLRecord(form, recorder.get(), page, 0, 0, width, height, 0, 0);
                image_file_name = WriteSkp(name.c_str(), page_index, recorder.get());
            }
            break;
#endif
            default:
                break;
            }

            // Write the filename and the MD5 of the buffer to stdout if we wrote a
            // file.
            //        if (options.md5 && !image_file_name.empty())
            //            OutputMD5Hash(image_file_name.c_str(), buffer, stride * height);

            //    FPDFText_ClosePage(text_page.get());
            FORM_DoPageAAction(page, form, FPDFPAGE_AACTION_CLOSE);
            FORM_OnBeforeClosePage(page, form);

            return outBuf;
        }

        bool PDFIumReader::RenderPdf(const std::string &name,
                                     const char *pBuf,
                                     size_t len,
                                     const Options &options,
                                     const std::string &events)
        {
            DEBUG_LOG_S(L_INFO) << qstring(name) << "file length:" << len;

            events_ = events;
            m_strFileName = name;

            loader_ = std::make_unique<PDFium>(pBuf, len);

            file_access = std::make_unique<FPDF_FILEACCESS>();
            ;
            file_access->m_FileLen = static_cast<unsigned long>(len);
            file_access->m_GetBlock = PDFium::GetBlock;
            file_access->m_Param = loader_.get();

            file_avail = std::make_unique<FX_FILEAVAIL>();
            file_avail->version = 1;
            file_avail->IsDataAvail = Is_Data_Avail;

            hints = std::make_unique<FX_DOWNLOADHINTS>();
            hints->version = 1;
            hints->AddSegment = Add_Segment;

            // The pdf_avail must outlive doc.
            pdf_avail_.reset(FPDFAvail_Create(file_avail.get(), file_access.get()));

            // The document must outlive |form_callbacks.loaded_pages|.
            //    ScopedFPDFDocument doc;

            bIsLinearized_ = FPDFAvail_IsLinearized(pdf_avail_.get()) == PDF_LINEARIZED;

            int nRet = PDF_DATA_NOTAVAIL;
            if (bIsLinearized_)
            {
                doc_.reset(FPDFAvail_GetDocument(pdf_avail_.get(), nullptr));
                if (doc_)
                {
                    while (nRet == PDF_DATA_NOTAVAIL)
                        nRet = FPDFAvail_IsDocAvail(pdf_avail_.get(), hints.get());

                    if (nRet == PDF_DATA_ERROR)
                    {
                        DEBUG_LOG_S(L_ERROR) << "Unknown error in checking if doc was available.";
                        return false;
                    }
                    nRet = FPDFAvail_IsFormAvail(pdf_avail_.get(), hints.get());
                    if (nRet == PDF_FORM_ERROR || nRet == PDF_FORM_NOTAVAIL)
                    {
                        DEBUG_LOG_S(L_ERROR) << "Error " << nRet << " was returned in checking if form was available.\n";
                        return false;
                    }
                }
            }
            else
            {
                doc_.reset(FPDF_LoadCustomDocument(file_access.get(), nullptr));
            }

            // result
            std::tuple<int, string> _error = PrintLastError();
            bCanLoad = std::get<0>(_error) == 0;
            if (!bCanLoad)
            {
                DEBUG_LOG_S(L_ERROR) << qstring(std::get<1>(_error));
                return bCanLoad;
            }

            //    unsigned long _permissions = FPDF_GetDocPermissions(doc.get());
            //    if (options.show_metadata)
            //        DumpMetaData(doc.get());

            m_nPageCount = FPDF_GetPageCount(doc_.get());

            if (options.save_attachments)
                WriteAttachments(doc_.get(), name);

#ifdef PDF_ENABLE_V8
            IPDF_JSPLATFORM platform_callbacks = {};
            platform_callbacks.version = 3;
            platform_callbacks.app_alert = ExampleAppAlert;
            platform_callbacks.app_beep = ExampleAppBeep;
            platform_callbacks.app_response = ExampleAppResponse;
            platform_callbacks.Doc_getFilePath = ExampleDocGetFilePath;
            platform_callbacks.Doc_mail = ExampleDocMail;
            platform_callbacks.Doc_print = ExampleDocPrint;
            platform_callbacks.Doc_submitForm = ExampleDocSubmitForm;
            platform_callbacks.Doc_gotoPage = ExampleDocGotoPage;
            platform_callbacks.Field_browse = ExampleFieldBrowse;
#endif // PDF_ENABLE_V8

#ifdef PDF_ENABLE_XFA
            form_callbacks.version = 2;
#else  // PDF_ENABLE_XFA
            form_callbacks.version = 1;
#endif // PDF_ENABLE_XFA

            form_callbacks.FFI_GetPage = GetPageForIndex;

#ifdef PDF_ENABLE_V8
            if (!options.disable_javascript)
                form_callbacks.m_pJsPlatform = &platform_callbacks;
#endif // PDF_ENABLE_V8

            form_.reset(FPDFDOC_InitFormFillEnvironment(doc_.get(), &form_callbacks));

            form_callbacks.form_handle = form_.get();

#ifdef PDF_ENABLE_XFA
            if (!options.disable_xfa && !options.disable_javascript)
            {
                int doc_type = FPDF_GetFormType(doc.get());
                if (doc_type == FORMTYPE_XFA_FULL || doc_type == FORMTYPE_XFA_FOREGROUND)
                {
                    if (!FPDF_LoadXFA(doc.get()))
                        fprintf(stderr, "LoadXFA unsuccessful, continuing anyway.\n");
                }
            }
#endif // PDF_ENABLE_XFA

            FPDF_SetFormFieldHighlightColor(form_.get(), FPDF_FORMFIELD_UNKNOWN, 0xFFE4DD);
            FPDF_SetFormFieldHighlightAlpha(form_.get(), 100);
            FORM_DoDocumentJSAction(form_.get());
            FORM_DoDocumentOpenAction(form_.get());

#if _WIN32
            if (options.output_format == OUTPUT_PS2)
                FPDF_SetPrintMode(FPDF_PRINTMODE_POSTSCRIPT2);
            else if (options.output_format == OUTPUT_PS3)
                FPDF_SetPrintMode(FPDF_PRINTMODE_POSTSCRIPT3);
#endif

            FORM_DoDocumentAAction(form_.get(), FPDFDOC_AACTION_WC);
        }

        bool PDFIumReader::Reader(const std::string &filename)
        {

            DEBUG_LOG_S(L_ERROR) << "begin";

            //    Options options;
            options_.output_format = OutputFormat::OUTPUT_BMP;

#ifdef PDF_ENABLE_V8
            std::unique_ptr<v8::Platform> platform;
#ifdef V8_USE_EXTERNAL_STARTUP_DATA
            v8::StartupData natives;
            v8::StartupData snapshot;
            platform = InitializeV8ForPDFiumWithStartupData(
                options.exe_path, options.bin_directory, &natives, &snapshot);
#else  // V8_USE_EXTERNAL_STARTUP_DATA
            platform = InitializeV8ForPDFium(options.exe_path);
#endif // V8_USE_EXTERNAL_STARTUP_DATA
#endif // PDF_ENABLE_V8

            FPDF_LIBRARY_CONFIG config;
            config.version = 2;
            config.m_pUserFontPaths = nullptr;
            config.m_pIsolate = nullptr;
            config.m_v8EmbedderSlot = 0;

            const char *path_array[2];
            if (!options_.font_directory.empty())
            {
                path_array[0] = options_.font_directory.c_str();
                path_array[1] = nullptr;
                config.m_pUserFontPaths = path_array;
            }
            FPDF_InitLibraryWithConfig(&config);

            UNSUPPORT_INFO unsupported_info = {};
            unsupported_info.version = 1;
            unsupported_info.FSDK_UnSupport_Handler = ExampleUnsupportedHandler;

            FSDK_SetUnSpObjProcessHandler(&unsupported_info);

            if (options_.time > -1)
            {
                // This must be a static var to avoid explicit capture,
                // so the lambda can be
                // converted to a function ptr.
                static time_t time_ret = options_.time;
                FSDK_SetTimeFunction([]()
                                     { return time_ret; });
                FSDK_SetLocaltimeFunction([](const time_t *tp)
                                          { return gmtime(tp); });
            }

            file_contents = GetFileContents(filename.c_str(), &file_length);
            if (file_length <= 0 || !file_contents)
            {
                DEBUG_LOG_S(L_ERROR) << "GetFileContents PDF file " << filename.c_str() << " error!";
                return false;
            }
            DEBUG_LOG_S(L_INFO) << "GetFileContents PDF file " << filename.c_str() << ".";

#ifdef ENABLE_CALLGRIND
            if (options.callgrind_delimiters)
                CALLGRIND_START_INSTRUMENTATION;
#endif // ENABLE_CALLGRIND

            if (options_.send_events)
            {
                std::string event_filename = filename;
                size_t event_length = 0;
                size_t extension_pos = event_filename.find(".pdf");
                if (extension_pos != std::string::npos)
                {
                    event_filename.replace(extension_pos, 4, ".evt");
                    if (access(event_filename.c_str(), R_OK) == 0)
                    {
                        fprintf(stderr, "Using event file %s.\n", event_filename.c_str());
                        std::unique_ptr<char, pdfium::FreeDeleter> event_contents =
                            GetFileContents(event_filename.c_str(), &event_length);
                        if (event_contents)
                        {
                            fprintf(stderr, "Sending events from: %s\n",
                                    event_filename.c_str());
                            events_ = std::string(event_contents.get(), event_length);
                        }
                    }
                }
            }

            return RenderPdf(filename, file_contents.get(), file_length, options_, events_);
        }

        bool PDFIumReader::GetPdfPage(int pageIndex, QByteArray *byteArray)
        {
            DEBUG_LOG_S(L_INFO) << (pageIndex);
            if (pageIndex < 0)
                return false;

            if (!byteArray)
            {
                return false;
            }

            if (!doc_)
            {
                DEBUG_LOG_S(L_ERROR) << "doc is invalid!";
                return false;
            }

            pageIndex = min(pageIndex, m_nPageCount - 1);
            m_nCurrentPage = pageIndex;

            return RenderPage(doc_.get(), form_.get(),
                              &form_callbacks,
                              pageIndex,
                              options_,
                              events_,
                              byteArray);
        }

        bool PDFIumReader::GetNextPage(QByteArray *byteArray)
        {
            return GetPdfPage(++m_nCurrentPage, byteArray);
        }

        bool PDFIumReader::GetPrevPage(QByteArray *byteArray)
        {
            return GetPdfPage(--m_nCurrentPage, byteArray);
        }

        void PDFIumReader::SetCurrentPage(int page)
        {
            m_nCurrentPage = page;
            m_nCurrentPage = min(m_nCurrentPage, GetPageCount() - 1);
            m_nCurrentPage = max(0, m_nCurrentPage);
        }

        void PDFIumReader::Close()
        {
            DEBUG_LOG_S(L_INFO) << ":" << this;
            if (!doc_)
            {
                DEBUG_LOG_S(L_ERROR) << "doc is invalid!";
                return;
            }

            FORM_DoDocumentAAction(form_.get(), FPDFDOC_AACTION_WC);
            //        FPDFDOC_ExitFormFillEnviroument(this->m_formHandle);
            FPDF_CloseDocument(doc_.get());
            FPDFAvail_Destroy(pdf_avail_.get());

            //    free(m_pdfBuf);
            //    this->m_pPdfDoc = NULL;
        }

        PDFIumLoader::PDFIumLoader(const char *pBuf, size_t len)
            : m_pBuf(pBuf), m_Len(len)
        {
        }

    }
}
