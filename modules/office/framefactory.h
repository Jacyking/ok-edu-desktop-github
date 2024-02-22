#ifndef FRAMEFACTORY_H
#define FRAMEFACTORY_H

#include <QString>
#include <QWidget>


namespace office {

class FrameFactory
{
public:
    FrameFactory();

    template<typename T>
    static T* Create(QWidget* parent){
           return new T(parent);
    }
};

}
#endif // FRAMEFACTORY_H
