#ifndef OMAINTITLEBAR_H
#define OMAINTITLEBAR_H

#include <QWidget>

namespace Ui {
class OMainTitleBar;
}

class OMainTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit OMainTitleBar(QWidget *parent = nullptr);
    ~OMainTitleBar();



private:
    Ui::OMainTitleBar *ui;
};


#endif // OMAINTITLEBAR_H
