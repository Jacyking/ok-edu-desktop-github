#ifndef PAINTEREVENT_H
#define PAINTEREVENT_H

#include "Base.h"
#include "PaintItem.h"
#include "SharedPaintManager.h"

#include <QString>


namespace painter {


class PainterEvent: public ICanvasViewEvent
{
public:
    PainterEvent();
    virtual ~PainterEvent() override;



    virtual void setManager(CSharedPaintManager* manager){
        _manager = manager;
    }

protected:

    //ICanvasViewEvent
    void onMoveItem(std::shared_ptr<CPaintItem> item) override;
    void onDrawItem(std::shared_ptr<CPaintItem> item) override;
    void onUpdateItem(std::shared_ptr<CPaintItem> item) override;
    void onRemoveItem(std::shared_ptr<CPaintItem> item) override;
    QString onGetToolTipText(std::shared_ptr<CPaintItem> item) override;
    virtual std::shared_ptr<CPaintItem> onFindItem(ItemId itemId ) override;

private:
    CSharedPaintManager* _manager;
};


}
#endif // PAINTEREVENT_H
