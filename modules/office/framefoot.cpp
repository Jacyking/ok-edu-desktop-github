#include "framefoot.h"


namespace office {


FrameFoot::FrameFoot(QWidget *parent) :
      MoveableBar(parent)
{
    setFixedHeight(50);

    layout_ = new QHBoxLayout(this);

}


}
