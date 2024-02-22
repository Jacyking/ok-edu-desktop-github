//
// Created by workg on 7/27/2018.
//
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
#include <QObject>
#include <QWidget>
#include <memory>

#ifdef Q_WEBENGINE
#include <QWebChannel>
#include <QWebEngineView>
#endif

#include "UI/window/page/Page.h"
#include "lib/network/backend/BaseService.h"

namespace UI {
namespace page {

class JsContext : public QObject {
  Q_OBJECT
public:
  explicit JsContext(QObject *parent = nullptr);

  void sendMsg(void *page, const QString &msg);

signals:
  void recvdMsg(const QString &, const QString &);

public slots:
  void onMsg(const QString &, const QString &);
};

class Calendar : public Page {
  Q_OBJECT
public:
  Calendar(QWidget *parent = nullptr);
  ~Calendar();

  virtual void showEvent(QShowEvent *e) override;

private:
#ifdef Q_WEBENGINE
  std::unique_ptr<QWebEngineView> _webView;
  std::unique_ptr<QWebChannel> m_webChannel;
#endif
  std::unique_ptr<JsContext> m_jsContext;
};

} // namespace page
} // namespace UI
