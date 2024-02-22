#include "painterevent.h"


namespace painter {


PainterEvent::PainterEvent()
{

}

PainterEvent::~PainterEvent()
{

}


void PainterEvent::onMoveItem(std::shared_ptr< CPaintItem > item )
{
    _manager->movePaintItem( item );
}

void PainterEvent::onDrawItem(std::shared_ptr<CPaintItem> item  )
{
    _manager->addPaintItem( item );
}

void PainterEvent::onUpdateItem(std::shared_ptr<CPaintItem> item )
{
    _manager->updatePaintItem( item );
}

void PainterEvent::onRemoveItem(std::shared_ptr<CPaintItem> item )
{
    _manager->removePaintItem( item );
}

QString PainterEvent::onGetToolTipText(std::shared_ptr<CPaintItem> item )
{
    DEBUG_LOG(("item posX:%1 posY:%2")
              .arg(item->posX()).arg(item->posY()))
            return "";
}

std::shared_ptr<CPaintItem> PainterEvent::onFindItem(ItemId itemId)
{
    DEBUG_LOG(("item id:%1").arg(qstring(itemId)));
    return _manager->findPaintItem("", itemId);
}

}
