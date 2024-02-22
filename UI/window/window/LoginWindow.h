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

#include <QMainWindow>
#include <memory>

#include "UI/window/widget/LoginWidget.h"

namespace Ui {
class LoginWindow;
class LoginWidget;
} // namespace Ui

namespace UI {

namespace window {

using namespace widget;

class LoginWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit LoginWindow(QWidget *parent = nullptr);
  ~LoginWindow();

private:
  Ui::LoginWindow *ui;

signals:
  void loginResult(ok::session::SignInInfo &, ok::session::LoginResult &);

public slots:
  void onProfileLoadFailed(QString msg);
};

} // namespace window
} // namespace UI
