
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <map>

#include <base/logs.h>

#include "PaintItem.h"

namespace painter
{

    class CSharedPaintItemList
    {
    public:
        typedef std::map<ItemId, std::shared_ptr<CPaintItem>> ITEM_MAP;

    public:
        CSharedPaintItemList(const std::string &owner) : owner_(owner) {}

        ~CSharedPaintItemList(void)
        {
        }

        bool addItem(std::shared_ptr<CPaintItem> item)
        {
            if (item->itemId().size() <= 0)
            {
                DEBUG_LOG_S(L_WARN) << "item id can't be empty!";
                return false;
            }

            auto s = itemMap_.find(item->itemId());
            if (s != itemMap_.end())
            {
                DEBUG_LOG_S(L_WARN) << "item is exist!";
                return false;
            }

            std::pair<ITEM_MAP::iterator, bool> ret = itemMap_.insert(ITEM_MAP::value_type(item->itemId(), item));
            if (!ret.second)
            {
                DEBUG_LOG_S(L_ERROR) << "item id:" << qstring(item->itemId());
                return false;
            }

            return true;
        }

        std::shared_ptr<CPaintItem> findItem(ItemId itemId)
        {
            ITEM_MAP::iterator it = itemMap_.find(itemId);
            if (it == itemMap_.end())
                return std::shared_ptr<CPaintItem>();

            return it->second;
        }

        void removeItem(ItemId itemId)
        {
            ITEM_MAP::iterator it = itemMap_.find(itemId);
            if (it == itemMap_.end())
                return;

            itemMap_.erase(it);
        }

        size_t itemCount(void) { return itemMap_.size(); }

        ITEM_MAP &itemMap()
        {
            return itemMap_;
        }

    private:
        std::string owner_;
        ITEM_MAP itemMap_;
    };
}
