#ifndef SMARTBOARDDRAWCONTROLLERVOICE_H
#define SMARTBOARDDRAWCONTROLLERVOICE_H

#include "smartboard.h"

namespace SmartBoard
{

    class ControllerVoice : public ControllerItem
    {
        private:

        public:
            ControllerVoice();
            ControllerVoice(const DrawId & id) : ControllerItem(id){};
    };

}
#endif // SMARTBOARDDRAWCONTROLLERVOICE_H
