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
#pragma once

#include <QFrame>
#include <QGraphicsProxyWidget>
#include <QGraphicsWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>


#include <lib/network/backend/BookedService.h>

#include "UI/window/widget/OWebView.h"
#include <UI/widget/MoveableBar.h>


namespace UI {

namespace widget {

enum BarArcDirection {
  TOP_LEFT = 0,
  TOP_RIGHT,
  BOTTOM_RIGHT,
  BOTTOM_LEFT,
};

class BarArc : public UI::widget::MoveableBar {
public:
  BarArc(BarArcDirection = TOP_LEFT, QWidget *parent = nullptr);
  ~BarArc();

private:
  BarArcDirection _direction;

  virtual void paintEvent(QPaintEvent *event);
};

class WebViewBar : public UI::widget::MoveableBar {
  Q_OBJECT
public:
  WebViewBar(QWidget *parent = nullptr);
  ~WebViewBar();
};

class MaterialView : public OWebView {
  Q_OBJECT

public:
  MaterialView(QWidget *parent = nullptr);

  ~MaterialView();

  void toggle(bool checked);

  virtual void showEvent(QShowEvent *event);

private:
  WebViewBar *_bar = nullptr;

  std::unique_ptr<ok::backend::BookedService> _bookedService;

signals:
  void loadBooked(ok::backend::BookedInfo);

public slots:
  void openBooked(ok::backend::BookedInfo);
};

} // namespace widget

} // namespace UI
