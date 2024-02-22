#include "BaseWindow.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QStyleOption>
#include <QGraphicsDropShadowEffect>

#include <base/utils.h>

BaseWindow::BaseWindow(QWidget *parent) : QWidget(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	// setAttribute(Qt::WA_TranslucentBackground);
}

BaseWindow::~BaseWindow()
{
}

void BaseWindow::paintEvent(QPaintEvent *event)
{
	return QWidget::paintEvent(event);
}
