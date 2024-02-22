#ifndef PAINTERRENDERER_H
#define PAINTERRENDERER_H

#include "SharedPaintManager.h"
#include "isharedpaintevent.h"

namespace painter {


class PainterRenderer:
        public ISharedPaintEvent
{
public:
    PainterRenderer();

    virtual void setSharedPainterScene(IGluePaintCanvas* scene){
        _scene = scene;
    }

protected:
    //ISharedPaintEvent
    virtual void onISharedPaintEvent_AddTask(int totalTaskCount, bool playBackWorking ) override;
    virtual void onISharedPaintEvent_AddPaintItem(std::shared_ptr<CPaintItem> item ) override;
    virtual void onISharedPaintEvent_RemovePaintItem(std::shared_ptr<CPaintItem> item) override;
    virtual void onISharedPaintEvent_MovePaintItem(std::shared_ptr<CPaintItem> item, double x, double y) override;

    virtual void onISharedPaintEvent_UpdatePaintItem( std::shared_ptr<CPaintItem> item) override;

private:

    //    std::unique_ptr<CSharedPaintManager> _manager;

    IGluePaintCanvas* _scene;
};


}
#endif // PAINTERRENDERER_H
