#pragma once

#include <memory>

#include "PaintItem.h"


namespace context {

namespace WB {

enum class WB_CTRL {
    MOVE = 0,	//移动
    MUTE,		//禁言
    WB,			//白板
    RE,			//选择
    OK,			//正确
    GIFT,		//奖励
    ALL,		//ALL
};

struct WB_CTRL_BTN {
    WB_CTRL type;
    int x;
    int y;
    QString icon;
    QString activeIcon;
    bool moveable;
    bool checkable;
};

}
}

namespace painter {

typedef enum  {
    P_MOVE = 0,
    P_TEXT,
    P_PEN,
    P_REMOVE,
    P_CUTTER,
    P_CLOUD,
} ToolboxType;

struct ToolboxMenu {
    ToolboxType type;
    QString name;    //menu name
};

struct ToolboxData {
    ToolboxType type;
    int width;
    QString color;
};

class CSharedPainterScene;
class CSharedPaintManager;

class ISharedPaintEvent;
class ICanvasViewEvent;


class ICanvasViewEvent {
public:
    ICanvasViewEvent(){}
    virtual ~ICanvasViewEvent(){}

    virtual void onMoveItem(std::shared_ptr<CPaintItem> item) = 0;

    virtual void onDrawItem(std::shared_ptr<CPaintItem> item) = 0;

    virtual void onUpdateItem(std::shared_ptr<CPaintItem> item) = 0;

    virtual void onRemoveItem(std::shared_ptr<CPaintItem> item) = 0;

    virtual QString onGetToolTipText(std::shared_ptr<CPaintItem> item) = 0;

    virtual std::shared_ptr<CPaintItem> onFindItem(ItemId itemId ) = 0;

};

}
