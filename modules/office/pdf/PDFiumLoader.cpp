#include "PDFiumLoader.h"

#include <string.h>


PDFiumLoader::PDFiumLoader(pdfium::span<const char> span) : m_Span(span) {
  
}

// static
int PDFiumLoader::GetBlock(void* param,
                         unsigned long pos,
                         unsigned char* pBuf,
                         unsigned long size) {
  PDFiumLoader* pLoader = static_cast<PDFiumLoader*>(param);
  if (pos + size < pos || pos + size > pLoader->m_Span.size()) {
    NOTREACHED();
    return 0;
  }

  memcpy(pBuf, &pLoader->m_Span[pos], size);
  return 1;
}
