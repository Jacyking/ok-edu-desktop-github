#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QDialog>
#include <QWidget>
#include "UI/window/widget/LoginTitleBar.h"

class BaseWindow : public QWidget
{
	Q_OBJECT

public:
	BaseWindow(QWidget *parent = 0);
	~BaseWindow();

protected:
	void paintEvent(QPaintEvent *event);

private slots:

protected:
};

#endif // BASEWINDOW_H
