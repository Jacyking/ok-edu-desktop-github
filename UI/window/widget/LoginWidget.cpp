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

#include "LoginWidget.h"

#include <QPaintEvent>
#include <QShortcut>
#include <QTranslator>
#include <QWidget>

#include "UI/core/SettingManager.h"
#include "base/logs.h"
#include "base/widgets.h"
#include "lib/settings/OkSettings.h"
#include "lib/settings/translator.h"
#include "ui_LoginWidget.h"

namespace UI {
namespace widget {

using namespace core;
using namespace ok::session;
using namespace ok::base;

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent),         //                                        //
      ui(new Ui::LoginWidget), //
      m_loginKey(nullptr), m_settingManager(nullptr) {


  ui->setupUi(this);

  //==========国际化==========//
  // 先获取当前语言
  OkSettings &s = OkSettings::getInstance();
  qDebug() << "Settings translation:" << s.getTranslation();

  for (int i = 0; i < s.getLocales().size(); ++i) {
    auto &locale = s.getLocales().at(i);
    QString langName = QLocale(locale).nativeLanguageName();
    ui->language->addItem(langName);
  }
  qDebug() << "Added languages ComboBox count is:" << ui->language->count();

  // 当前语言状态
  auto i = s.getLocales().indexOf(s.getTranslation());
  qDebug() << "Set current index for language=>" << i;

  if (i >= 0 && i < ui->language->count())
    ui->language->setCurrentIndex(i + 1);

  settings::Translator::registerHandler(
      std::bind(&LoginWidget::retranslateUi, this), this);

  retranslateUi();
  //==========国际化==========//

  /**
   * 安装事件过滤器
   */
  ui->signUp->installEventFilter(this);
  ui->findPwd->installEventFilter(this);

  /**
   * 增加快捷键
   */
  m_loginKey = new QShortcut(QKeySequence(Qt::Key_Return), this);
  connect(m_loginKey, SIGNAL(activated()), //
          this, SLOT(on_loginBtn_released()));

  // 初始化
  init();

}

LoginWidget::~LoginWidget() {
  // 卸载语言处理器
  settings::Translator::unregister(this);
  disconnect(m_loginKey);
  delete m_loginKey;
  delete ui;
}

void LoginWidget::init() {
  m_settingManager = SettingManager::InitGet();
  m_settingManager->getAccount([&](QString acc, QString password) {
    ui->rember->setChecked(!acc.isEmpty());
    ui->accountInput->setText(acc);
    ui->passwordInput->setText(password);
  });
}

void LoginWidget::doLogin() {

  // 对登录时状态判断
  auto status = ok::session::AuthSession::Instance()->status();

  switch (status) {
  case ok::session::Status::SUCCESS: {
    DEBUG_LOG(("SUCCESS ..."));
    return;
  }
  case ok::session::Status::CONNECTING: {
    DEBUG_LOG(("CONNECTING ..."));
    //    sess->interrupt();
    return;
  }
  default: {
    DEBUG_LOG(("Login ..."));
    // 登陆
    QString account(ui->accountInput->text());
    QString password(ui->passwordInput->text());
    // 对账号和密码判断
    if (account.isEmpty()) {
      return;
    }
    if (ui->rember->isCheckable()) {
      m_settingManager->saveAccount(account, password);
    } else {
      m_settingManager->clearAccount();
    }

    SignInInfo info{account, password};
    auto _session = ok::session::AuthSession::Instance();
    connect(_session, &AuthSession::loginResult, //
            this, &LoginWidget::onConnectResult);
    _session->doLogin(info);
    break;
  }
  }
}

void LoginWidget::onConnectResult(ok::session::SignInInfo info,
                                  ok::session::LoginResult result) {

  DEBUG_LOG(("msg:%1").arg(result.msg));

  switch (result.status) {
  case ok::session::Status::NONE:
    break;
  case ok::session::Status::CONNECTING: {
    ui->loginMessage->setText(tr("..."));
    QString account(ui->accountInput->text());
    QString password(ui->passwordInput->text());
    emit loginFailed(account, password);
    break;
  }
  case ok::session::Status::SUCCESS: {
    ui->loginMessage->setText(tr("login success"));
    QString account(ui->accountInput->text());
    QString password(ui->passwordInput->text());
    emit loginSuccess(account, password);
    break;
  }
  case ok::session::Status::FAILURE:
    ui->loginMessage->setText(result.msg);
    break;
  }
  emit loginResult(info, result);
}

void LoginWidget::on_loginBtn_released() { doLogin(); }

void LoginWidget::on_language_currentIndexChanged(int index) {
  qDebug() << "Select language:" << index;

  if (index == 0) {
    return;
  }

  OkSettings &s = OkSettings::getInstance();
  const QString &locale = s.getLocales().at(index - 1);
  qDebug() << "Selected locale:" << locale;

  s.setTranslation(locale);

  qDebug() << "Translate locale:" << locale;
  settings::Translator::translate(OK_UIWindow_MODULE, locale);
  s.saveGlobal();
}

void LoginWidget::retranslateUi() { ui->retranslateUi(this); }

void LoginWidget::onError(const QString &msg) {
  ui->loginMessage->setText(msg);
}

bool LoginWidget::eventFilter(QObject *obj, QEvent *event) {
  switch (event->type()) {
  case QEvent::MouseButtonPress: {
    if (obj == ui->signUp) {
      QDesktopServices::openUrl(
          QUrl("http://stack.okstar.org.cn/auth/register"));
    } else if (obj == ui->findPwd) {
      QDesktopServices::openUrl(
          QUrl("http://stack.okstar.org.cn/auth/forgot"));
    }
    break;
  }
  default:
    break;
  };
  return QObject::eventFilter(obj, event);
}

} // namespace widget
} // namespace UI
