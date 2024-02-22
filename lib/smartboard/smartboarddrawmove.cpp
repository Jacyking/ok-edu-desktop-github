#include "smartboarddrawmove.h"

namespace SmartBoard
{
    DrawMove::DrawMove()
    {
    }

    void DrawMove::setMoveId(const DrawId &id)
    {
        _id = id;
    }

    const DrawId& DrawMove::moveId() const {
        return _id;
    }

    void DrawMove::setPosition(const Position &position)
    {
        _position = position;
    }

    const Position& DrawMove::position() const {
        return _position;
    }


}
