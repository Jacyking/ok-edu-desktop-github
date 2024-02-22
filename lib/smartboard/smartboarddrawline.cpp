#include "smartboarddrawline.h"

namespace SmartBoard
{

    DrawLine::DrawLine() : DrawItem()
    {

    }
    
    DrawLine::DrawLine(const std::string &id, const PointList &lists): DrawItem()
    {
        _id = id;
        _type = DrawType::Line;
        _lists = lists;
    }

   
}
