#ifndef SMARTBOARDDRAWLINE_H
#define SMARTBOARDDRAWLINE_H
#include "smartboard.h"

namespace SmartBoard
{

    class DrawLine : public DrawItem
    {
    private:
         PointList _lists;
    
    public:
        DrawLine();
        DrawLine(const std::string &id, const PointList &lists);
    };

}
#endif // SMARTBOARDDRAWLINE_H
