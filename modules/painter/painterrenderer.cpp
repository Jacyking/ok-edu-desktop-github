#include "painterrenderer.h"


namespace painter {


PainterRenderer::PainterRenderer()
{

}


void PainterRenderer::onISharedPaintEvent_AddTask(int totalTaskCount, bool playBackWorking)
{
    DEBUG_LOG(("totalTaskCount:%1 playBackWorking:%2")
              .arg(totalTaskCount)
              .arg(playBackWorking));
}

void PainterRenderer::onISharedPaintEvent_AddPaintItem(std::shared_ptr<CPaintItem> item)
{
    DEBUG_LOG(("item id:%1 posX:%2 posY:%3")
              .arg(qstring(item->itemId()))
              .arg(item->posX())
              .arg(item->posY()))

    item->setCanvas(_scene);
    item->draw();
}

void PainterRenderer::onISharedPaintEvent_RemovePaintItem(std::shared_ptr<CPaintItem> item)
{
    DEBUG_LOG(("item id:%1 posX:%2 posY:%3")
              .arg(qstring(item->itemId()))
              .arg(item->posX())
              .arg(item->posY()))
    item->remove();
}

void PainterRenderer::onISharedPaintEvent_MovePaintItem(std::shared_ptr<CPaintItem> item, double x, double y)
{

}

void PainterRenderer::onISharedPaintEvent_UpdatePaintItem(std::shared_ptr<CPaintItem> item)
{
    DEBUG_LOG(("item id:%1 posX:%2 posY:%3")
              .arg(qstring(item->itemId()))
              .arg(item->posX())
              .arg(item->posY()))

    item->update();
}

}
