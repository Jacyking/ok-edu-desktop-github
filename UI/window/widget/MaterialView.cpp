/*
    Copyright © 2014-2019 by The qTox Project Contributors

    This file is part of qTox, a Qt-based graphical interface for Tox.

    qTox is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    qTox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with qTox.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "MaterialView.h"
#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#ifdef Q_WEBENGINE
#include <QWebEngineSettings>
#include <QWebEngineView>

#endif

#include "base/r.h"
#include <base/logs.h>
#include <base/widgets.h>

#include "lib/session/AuthSession.h"
#include "UI/window/widget/OWebView.h"
#include <UI/widget/MoveableBar.h>

namespace UI {

namespace widget {

BarArc::BarArc(BarArcDirection dir, QWidget *parent)
    : UI::widget::MoveableBar(parent), _direction(dir) {
  setFixedSize(QSize(60, 60));
}

BarArc::~BarArc() {}

void BarArc::paintEvent(QPaintEvent *event) {

  qDebug() << "paintEvent";

  QPoint startPt(0, 0);
  QRect rect(startPt, this->size());

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing); // 抗锯齿
  p.fillRect(rect, Qt::transparent);

  int arcR = rect.width() / 2;
  int rectSize = rect.width();

  QPainterPath path;
  path.moveTo(startPt.x() + arcR, startPt.y() + arcR); // 先移动到圆心

  switch (_direction) {
  case BarArcDirection::TOP_LEFT:
    path.arcTo(rect, 00.0f, -90.0f);
    break;
  case BarArcDirection::TOP_RIGHT:
    path.arcTo(rect, 180.0f, 90.0f);
    break;
  case BarArcDirection::BOTTOM_RIGHT:
    path.arcTo(rect, 90.0f, 90.0f);
    break;
  case BarArcDirection::BOTTOM_LEFT:
    path.arcTo(rect, 0.0f, 90.0f);
    break;
  default:
    break;
  }

  p.fillPath(path, QBrush(QColor("#535353")));
}

WebViewBar::WebViewBar(QWidget *parent) : UI::widget::MoveableBar(parent) {}

WebViewBar::~WebViewBar() {}

MaterialView::MaterialView(QWidget *parent) : OWebView(parent) {
  setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

  setFixedSize(MATERIAL_VIEWPORT_WIDTH, MATERIAL_VIEWPORT_HEIGHT);
  setContentsMargins(QMargins(5, 5, 5, 5));

  base::Widgets::SetPalette(this, QPalette::Background, QColor("#535353"));

  BarArc *arc0 = new BarArc(BarArcDirection::TOP_LEFT, this);
  arc0->move(-30, -30);

  BarArc *arc1 = new BarArc(BarArcDirection::TOP_RIGHT, this);
  arc1->move(width() - 30, -30);

  BarArc *arc2 = new BarArc(BarArcDirection::BOTTOM_RIGHT, this);
  arc2->move(width() - 30, height() - 30);

  BarArc *arc3 = new BarArc(BarArcDirection::BOTTOM_LEFT, this);
  arc3->move(-30, height() - 30);

  qRegisterMetaType<ok::backend::BookedInfo>("backend::BookedInfo");
  connect(this, SIGNAL(loadBooked(ok::backend::BookedInfo)), this,
          SLOT(openBooked(ok::backend::BookedInfo)));
}

MaterialView::~MaterialView() {}

void MaterialView::toggle(bool checked) {
  if (checked) {
    show();
  } else {
    hide();
  }
}

void MaterialView::showEvent(QShowEvent *event) {

  if (!_bookedService.get()) {
    _bookedService = std::make_unique<ok::backend::BookedService>(
        ok::session::AuthSession::Instance());
  }

  _bookedService->requestCurrent(
      [this](ok::backend::BookedInfo info) { emit loadBooked(info); });
}

void MaterialView::openBooked(ok::backend::BookedInfo info) {
  if (0 < info.getId()) {
    QString baseUrl = _bookedService->baseUrl();
    QUrl url((baseUrl + "/material/preview.do?bookedId=%1").arg(info.getId()));
    openWeb(url);
  }
}

} // namespace widget
} // namespace UI
