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
#include "WhiteboardWidget.h"

#include <memory>
#include <future>

#include <QLabel>
#include <QImage>
#include <QPalette>
#include <QPushButton>
#include <base/utils.h>
#include <base/logs.h>

#ifdef Q_WEBENGINE
#include <QWebEngineView>
#endif

#include "base/r.h"

namespace UI
{

    namespace widget
    {

        WhiteboardWidget::WhiteboardWidget(QWidget *parent) : QFrame(parent)
        {
            //    if (parent) {
            //        setGeometry(parent->contentsRect());
            //    }
            //    setObjectName("WhiteboardWidget");
            //    setContentsMargins(QMargins(10, 10, 10, 10));

            //    _painter = std::make_unique<PainterWidget>(this);

            //    setStyleSheet("QFrame#WhiteboardWidget{background: white; border: 1px solid #ccc; border-radius: 10px}");
        }

        WhiteboardWidget::~WhiteboardWidget()
        {
        }

    }
}
