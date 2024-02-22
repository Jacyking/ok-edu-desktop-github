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
#include <QWidget>

#include <base/basic_types.h>

#include "UI/window/page/Page.h"
#include "UI/window/page/email.h"


namespace UI {
namespace page {

EMail::EMail(QWidget *parent) : Page(parent) {

  setAutoFillBackground(true);
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, QColor("#aaaaaa"));
  setPalette(palette);

  setObjectName(qsl("Page:%1").arg(static_cast<int>(PageMenu::email)));
}

EMail::~EMail() {}
} // namespace page

} // namespace UI
