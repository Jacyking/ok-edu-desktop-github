
#pragma once

#include <memory>
#include <cassert>

#include "PaintItem.h"

namespace painter {

    class CPaintItemFactory {
    public:
        static std::shared_ptr<CPaintItem> createItem(const ItemId& id, PaintItemType type) {
            std::shared_ptr<CPaintItem> item;
            switch (type) {
                case PT_LINE:
                    item = std::make_shared<CLineItem>(id);
                    break;
                case PT_FILE:
                    item = std::make_shared<CFileItem>(id);
                    break;
                case PT_TEXT:
                    item = std::make_shared<CTextItem>(id);
                    break;
                case PT_IMAGE_FILE:
                    item = std::make_shared<CImageFileItem>(id);
                    break;
                case PT_IMAGE:
                    item = std::make_shared<CImageItem>(id);
                    break;
                default:
                    assert(false && "not supported item type");
            }
            return item;
        }
    };

}
