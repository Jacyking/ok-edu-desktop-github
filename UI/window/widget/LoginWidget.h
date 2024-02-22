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

#include "UI/window/widget/OWidget.h"
#include "lib/session/AuthSession.h"

class QShortcut;
class QPaintEvent;

namespace core {
class SettingManager;
}

namespace Ui {
class LoginWidget;
}

namespace ok {
namespace session {
class AuthSession;
}
} // namespace ok

namespace UI {

namespace widget {

class LoginWidget : public QWidget {
  Q_OBJECT
public:
  explicit LoginWidget(QWidget *parent = nullptr);
  ~LoginWidget() override;
  void onError(const QString &msg);
  void init();
  void showMainWindow();

protected:
  void retranslateUi();
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  Ui::LoginWidget *ui;

  QShortcut *m_loginKey;

  core::SettingManager *m_settingManager;

signals:
  void loginSuccess(QString name, QString password);
  void loginFailed(QString name, QString password);
  void loginTimeout(QString name);
  void loginResult(ok::session::SignInInfo &info,
                   ok::session::LoginResult &result);

private slots:
  void doLogin();
  void onConnectResult(ok::session::SignInInfo info,
                       ok::session::LoginResult result);
  void on_loginBtn_released();
  void on_language_currentIndexChanged(int index);
};

} // namespace widget
} // namespace UI
