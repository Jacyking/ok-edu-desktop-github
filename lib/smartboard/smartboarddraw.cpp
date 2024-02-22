#include "smartboarddraw.h"

namespace SmartBoard
{

    SmartBoardDraw::SmartBoardDraw()
    {
    }

    const std::string &SmartBoardDraw::id() const
    {
        return _id;
    }

    Style &SmartBoardDraw::style()
    {
        return _style;
    }

    const Point &SmartBoardDraw::point() const
    {
        return _point;
    }

    const Position& SmartBoardDraw::position() const
    {
        return _position;
    }

    void SmartBoardDraw::setPosition(const Position& position)
    {
        _position = position;
    }

    // end of SmartBoard
}
