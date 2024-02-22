/** Copyright (c) 2022 船山信息 chuanshaninfo.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan
PubL v2. You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.
*/
#include "OResizeWidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <base/widgets.h>

namespace UI
{
    namespace widget
    {

        OResizeWidget::OResizeWidget(QWidget *parent) : OWidget(parent)
        {
            dir = (Direction::NONE);
            isLeftPressDown = false;

            frame_ = new QFrame(this);
            frame_->setGeometry(10, 10, width() - 20, height() - 20);
            base::Widgets::SetPalette(frame_, QPalette::Window, QColor("#535353"));

            this->setContentsMargins(20, 20, 20, 20);

            this->setMinimumHeight(100);
            this->setMinimumWidth(150);

            this->setMouseTracking(true);
        }

        void OResizeWidget::mouseReleaseEvent(QMouseEvent *event)
        {
            if (event->button() == Qt::LeftButton)
            {
                isLeftPressDown = false;
                if (dir != Direction::NONE)
                {
                    this->releaseMouse();
                    this->setCursor(QCursor(Qt::ArrowCursor));
                }
            }
        }

        void OResizeWidget::mousePressEvent(QMouseEvent *event)
        {
            switch (event->button())
            {
            case Qt::LeftButton:
                isLeftPressDown = true;
                if (dir != NONE)
                {
                    this->mouseGrabber();
                }
                else
                {
                    dragPosition = event->globalPos() - this->frameGeometry().topLeft();
                }
                break;
            case Qt::RightButton:
                this->close();
                break;
            default:
                OWidget::mousePressEvent(event);
            }
        }

        void OResizeWidget::paintEvent(QPaintEvent *event)
        {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(0, 0, this->width(), this->height());

            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing, true);
            painter.fillPath(path, QBrush(Qt::white));

            QColor color(0, 0, 0, 50);
            for (int i = 0; i < 10; i++)
            {
                QPainterPath path;
                path.setFillRule(Qt::WindingFill);
                path.addRect(10 - i, 10 - i, this->width() - (10 - i) * 2, this->height() - (10 - i) * 2);
                color.setAlpha(150 - qSqrt(i) * 50);
                painter.setPen(color);
                painter.drawPath(path);
            }
        }

        void OResizeWidget::mouseMoveEvent(QMouseEvent *event)
        {
            QPoint gloPoint = event->globalPos();
            QRect rect = this->rect();
            QPoint tl = mapToGlobal(rect.topLeft());
            QPoint rb = mapToGlobal(rect.bottomRight());

            if (!isLeftPressDown)
            {
                this->region(gloPoint);
            }
            else
            {

                if (dir != NONE)
                {
                    QRect rMove(tl, rb);

                    switch (dir)
                    {
                    case LEFT:
                        if (rb.x() - gloPoint.x() <= this->minimumWidth())
                            rMove.setX(tl.x());
                        else
                            rMove.setX(gloPoint.x());
                        break;
                    case RIGHT:
                        rMove.setWidth(gloPoint.x() - tl.x());
                        break;
                    case UP:
                        if (rb.y() - gloPoint.y() <= this->minimumHeight())
                            rMove.setY(tl.y());
                        else
                            rMove.setY(gloPoint.y());
                        break;
                    case DOWN:
                        rMove.setHeight(gloPoint.y() - tl.y());
                        break;
                    case LEFTTOP:
                        if (rb.x() - gloPoint.x() <= this->minimumWidth())
                            rMove.setX(tl.x());
                        else
                            rMove.setX(gloPoint.x());
                        if (rb.y() - gloPoint.y() <= this->minimumHeight())
                            rMove.setY(tl.y());
                        else
                            rMove.setY(gloPoint.y());
                        break;
                    case RIGHTTOP:
                        rMove.setWidth(gloPoint.x() - tl.x());
                        rMove.setY(gloPoint.y());
                        break;
                    case LEFTBOTTOM:
                        rMove.setX(gloPoint.x());
                        rMove.setHeight(gloPoint.y() - tl.y());
                        break;
                    case RIGHTBOTTOM:
                        rMove.setWidth(gloPoint.x() - tl.x());
                        rMove.setHeight(gloPoint.y() - tl.y());
                        break;
                    default:

                        break;
                    }
                    this->setGeometry(rMove);
                }
                else
                {
                    //            move(event->globalPos() - dragPosition);
                    event->accept();
                }
            }

            OWidget::mouseMoveEvent(event);
        }

        void OResizeWidget::region(const QPoint &cursorGlobalPoint)
        {
            QRect rect = this->rect();
            QPoint tl = mapToGlobal(rect.topLeft());
            QPoint rb = mapToGlobal(rect.bottomRight());
            int x = cursorGlobalPoint.x();
            int y = cursorGlobalPoint.y();

            if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y)
            {
                // 左上角
                dir = LEFTTOP;
                this->setCursor(QCursor(Qt::SizeFDiagCursor));
            }
            else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y())
            {
                // 右下角
                dir = RIGHTBOTTOM;
                this->setCursor(QCursor(Qt::SizeFDiagCursor));
            }
            else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y())
            {
                //左下角
                dir = LEFTBOTTOM;
                this->setCursor(QCursor(Qt::SizeBDiagCursor));
            }
            else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING)
            {
                // 右上角
                dir = RIGHTTOP;
                this->setCursor(QCursor(Qt::SizeBDiagCursor));
            }
            else if (x <= tl.x() + PADDING && x >= tl.x())
            {
                // 左边
                dir = LEFT;
                this->setCursor(QCursor(Qt::SizeHorCursor));
            }
            else if (x <= rb.x() && x >= rb.x() - PADDING)
            {
                // 右边
                dir = RIGHT;
                this->setCursor(QCursor(Qt::SizeHorCursor));
            }
            else if (y >= tl.y() && y <= tl.y() + PADDING)
            {
                // 上边
                dir = UP;
                this->setCursor(QCursor(Qt::SizeVerCursor));
            }
            else if (y <= rb.y() && y >= rb.y() - PADDING)
            {
                // 下边
                dir = DOWN;
                this->setCursor(QCursor(Qt::SizeVerCursor));
            }
            else
            {
                // 默认
                dir = NONE;
                this->setCursor(QCursor(Qt::ArrowCursor));
            }
        }

        QFrame *OResizeWidget::frame() const
        {
            return frame_;
        }

    }
}
