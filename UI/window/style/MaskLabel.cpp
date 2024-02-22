#include "MaskLabel.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

MaskLabel::MaskLabel(QWidget *parent) : QLabel(parent)
{
}

MaskLabel::~MaskLabel()
{

}

void MaskLabel::paintEvent(QPaintEvent *e) {
	if (pixmap()) {
		QPainter painter(this);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
		
		int round = qMin(width(), height());

		QPainterPath path; 
		path.addEllipse(0, 0, round, round); 
		painter.setPen(Qt::white);
		painter.setClipPath(path);
		painter.drawPixmap(0, 0, width(), height(), *pixmap());
	}
	else {
		QLabel::paintEvent(e);
	}
}