#pragma once

#include <QLabel>
#include <QWidget>
class MaskLabel : public QLabel
{
	Q_OBJECT

public:
	MaskLabel(QWidget *parent);
	~MaskLabel();

protected: void paintEvent(QPaintEvent *);
};
