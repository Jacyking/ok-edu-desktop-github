/*
 * Copyright (c) 2022 船山信息 chuanshaninfo.com
 * OkEDU is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PubL v2. You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#pragma once

#include "UI/window/page/Page.h"

class OVideoViewport;

namespace Ui {
class PageClassing;
}

namespace UI {
namespace page {

class PageClassing : public Page {
  Q_OBJECT

public:
  explicit PageClassing(QWidget *parent = nullptr);
  ~PageClassing();

  virtual const OVideoViewport *videoViewport() const;

  void toggleChat(bool checked);

private:
  Ui::PageClassing *ui;
};

} // namespace page
} // namespace UI

