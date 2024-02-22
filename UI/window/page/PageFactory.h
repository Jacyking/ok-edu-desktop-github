
#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H

#include <QWidget>


namespace UI {
namespace page {

class PageFactory{

public:
    template<typename T>
    static
      //Restrict type T to Page
      typename std::enable_if<true, Page>::type //T -> Page
      *Create(QWidget *parent = Q_NULLPTR){
        return new T(parent);
    }

};

}
}

#endif // PAGEFACTORY_H
