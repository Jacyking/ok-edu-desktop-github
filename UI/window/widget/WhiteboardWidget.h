﻿/** Copyright (c) 2022 船山信息 chuanshaninfo.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan
PubL v2. You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.
*/
#pragma once

#include <memory>

#include <QFrame>
#include <QVBoxLayout>

//#include "UI/window/widget/PainterWidget.h"

namespace UI {

namespace widget {

class WhiteboardWidget : public QFrame
{
    Q_OBJECT
public:
    WhiteboardWidget(QWidget *parent);

    ~WhiteboardWidget();


//    PainterWidget* painter() {
//        return   _painter.get() ;
//    }

private:

//    std::unique_ptr<PainterWidget> _painter;

};

}
}
