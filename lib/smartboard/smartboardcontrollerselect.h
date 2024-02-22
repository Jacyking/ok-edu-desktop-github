#ifndef SMARTBOARDCONTROLLERSELECT_H
#define SMARTBOARDCONTROLLERSELECT_H

#include "smartboard.h"


namespace SmartBoard
{

    class ControllerSelect : public ControllerItem
    {
    public:
        ControllerSelect();
        ControllerSelect(const DrawId &id) : ControllerItem(id){};
    };
}

#endif // SMARTBOARDCONTROLLERSELECT_H
