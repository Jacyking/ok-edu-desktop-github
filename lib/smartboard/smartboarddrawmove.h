#ifndef SMARTBOARDDRAWMOVE_H
#define SMARTBOARDDRAWMOVE_H

#include "smartboard.h"

namespace SmartBoard
{

    class DrawMove : public DrawItem
    {
    private:
        DrawId _id;
        Position _position;

    public:
        DrawMove();

        const DrawId& moveId() const;
        void setMoveId(const DrawId &);

        void setPosition(const Position &);
        const Position& position() const;
    };
}

#endif // SMARTBOARDDRAWMOVE_H
