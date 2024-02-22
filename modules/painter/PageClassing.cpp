/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * OkEDU is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE. See the
 * Mulan PubL v2 for more details.
 */

#include "PageClassing.h"
#include "OPainterViewport.h"
#include "Painter.h"
#include "ui_PageClassing.h"

namespace UI {
namespace page {


PageClassing::PageClassing(QWidget *parent)
    : Page(parent), //
      ui(new Ui::PageClassing) {
  ui->setupUi(this);
  setObjectName(qsl("Page:%1").arg(static_cast<int>(PageMenu::classing)));
}

PageClassing::~PageClassing() { delete ui; }

const OVideoViewport *PageClassing::videoViewport() const {
  return ui->video_viewport;
}

void PageClassing::toggleChat(bool checked) {
  ui->painter_viewport->toggleChat(checked);
}

} // namespace page
} // namespace UI
