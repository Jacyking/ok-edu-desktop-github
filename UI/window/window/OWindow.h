#ifndef OWINDOW_H
#define OWINDOW_H

#include <QDialog>


namespace UI {
namespace window {


class OWindow : public QDialog
{
public:
   explicit OWindow(QWidget *parent = nullptr,
                    Qt::WindowFlags f = Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    virtual ~OWindow() override{}
};


}
}
#endif // OWINDOW_H
