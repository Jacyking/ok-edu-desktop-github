//
// Created by workg on 7/27/2018.
//
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
#include "UI/window/page/calendar.h"
#include <QString>
#include <QUrl>
#include <QWidget>
#include <memory>

#ifdef Q_WEBENGINE
#include <QWebChannel>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineView>
#endif

#include <QDesktopServices>
#include <base/basic_types.h>

#include "UI/core/ui.h"
#include "UI/window/page/Page.h"

#include "base/r.h"

#include <lib/network/backend/BaseService.h>

namespace UI {
namespace page {

JsContext::JsContext(QObject *parent) : QObject(parent) {}

void JsContext::onMsg(const QString &cmd, const QString &data) {
  emit recvdMsg(cmd, data);
}

void JsContext::sendMsg(void *page, const QString &msg) {}

Calendar::Calendar(QWidget *parent) : Page(parent) {

  setAutoFillBackground(true);

  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, QColor("#bbaacc"));
  setPalette(palette);

  QWidget::setObjectName(
      qsl("Page:%1").arg(static_cast<int>(PageMenu::calendar)));
}

Calendar::~Calendar() {}

void Calendar::showEvent(QShowEvent *e) {
  Q_UNUSED(e);

#ifdef Q_WEBENGINE

  if (_webView.get()) {
    return;
  }

  _webView = std::make_unique<QWebEngineView>(this);
  _webView->setFixedSize(this->size());
  _webView->page()->profile()->clearHttpCache();

  AuthSession *s = AuthSession::Instance();

  QString url = qsl("%1/%2?uin=%3")
                    .arg(BACKEND_BASE_URL)
                    .arg("/calendar.do")
                    .arg(s->uin());
  _webView->load(QUrl(url));

  m_jsContext = std::make_unique<JsContext>(this);

  m_webChannel = std::make_unique<QWebChannel>(this);

  m_webChannel->registerObject("context", m_jsContext.get());

  _webView->page()->setWebChannel(m_webChannel.get());

  QObject::connect(m_jsContext.get(), &JsContext::recvdMsg, this,
                   [](const QString &msg, const QString &data) {
                     if (msg.compare("openUrl") == 0) {
                       QDesktopServices::openUrl(QUrl(data));
                     }
                   });

  _webView->show();
#endif
}
} // namespace page

} // namespace UI
