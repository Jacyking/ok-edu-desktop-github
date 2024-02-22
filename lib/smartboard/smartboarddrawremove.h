#ifndef SMARTBOARDDRAWREMOVE_H
#define SMARTBOARDDRAWREMOVE_H

#include "smartboard.h"

namespace SmartBoard
{

    class DrawRemove : public DrawItem
    {
        private:
            DrawId _id;


        public:
            DrawRemove();

            void setRemoveId(const DrawId &);
            const DrawId &removeId() const;
    };
}
#endif // DrawRemove_H
