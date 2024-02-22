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
#ifndef ORESIZEWIDGET_H
#define ORESIZEWIDGET_H

#include "OWidget.h"

#include <QMouseEvent>


namespace UI {
namespace widget {

#define PADDING 2

class OResizeWidget : public OWidget
{
    Q_OBJECT
public:
    enum Direction {
                 NONE = 0 ,
                 UP , DOWN,
                 LEFT, RIGHT,
                 LEFTTOP, LEFTBOTTOM,
                 RIGHTBOTTOM, RIGHTTOP,
                 };

    explicit OResizeWidget(QWidget* parent=nullptr);

    virtual ~OResizeWidget() override {}



protected:
    QFrame *frame() const;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    void region(const QPoint &cursorPoint);

private:
    QFrame* frame_;

    bool isLeftPressDown;
    QPoint dragPosition;
    Direction dir;
};


}
}
#endif // ORESIZEWIDGET_H
