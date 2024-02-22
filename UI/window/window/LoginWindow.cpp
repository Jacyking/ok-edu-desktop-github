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

#include "LoginWindow.h"


#include "base/r.h"
#include "UI/resources.h"
#include "ui_LoginWindow.h"
#include "UI/window/widget/LoginWidget.h"

namespace UI {

namespace window {

using namespace ok::session;
using namespace widget;

#define BANNER_WIDTH LOGIN_WINDOW_WIDTH * 0.6

/* 登录主窗口 */
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow) {
  ui->setupUi(this);

  setAttribute(Qt::WA_DeleteOnClose, true);

  setWindowTitle(APPLICATION_NAME);
  setFixedSize(LOGIN_WINDOW_WIDTH, LOGIN_WINDOW_HEIGHT);

  // 设置样式
  QString qss = utils::Resources::loadQss(utils::QSS::login);
  setStyleSheet(qss);

  connect(ui->loginWidget, &LoginWidget::loginResult,
          [&](ok::session::SignInInfo &info,  //
              ok::session::LoginResult &result) {
            emit loginResult(info, result);
          });
}

LoginWindow::~LoginWindow() {
//  Q_CLEANUP_RESOURCE(translations_UIWindow);
  delete ui;
}
void LoginWindow::onProfileLoadFailed(QString msg) {
  ui->loginWidget->onError(msg);
}

} // namespace window
} // namespace UI
