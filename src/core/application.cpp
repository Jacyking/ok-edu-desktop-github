﻿#include "application.h"

#include <memory>

#include "UI/core/FontManager.h"
#include "UI/window/window/LoginWindow.h"
#include "base/logs.h"
#include "im/src/nexus.h"
#include "launcher.h"
#include "lib/network/backend/domain/UserInfo.h"
#include "lib/plugin/pluginmanager.h"
#include "lib/settings/translator.h"
#include "base/r.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QString>
#include <QTranslator>
#include "modules/painter/Painter.h"

using namespace core;
using namespace base;

namespace core {

Application::Application(core::Launcher *launcher, int &argc, char *argv[])
    : QApplication(argc, argv), _argc(argc), _argv(argv) {
  qDebug() << (qstring("Cleanup..."));

  DEBUG_LOG(("argc:%1").arg(argc));
  for (int i = 0; i < argc; i++) {
    DEBUG_LOG(("argv:%1->%2").arg(argc).arg(argv[i]));
  }

#if QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
  setDesktopFileName(APPLICATION_ID);
#endif

  setApplicationName(qsl(APPLICATION_NAME));
  setApplicationVersion("\nGit commit: " + QString(GIT_VERSION));

  // Windows platform plugins DLL hell fix
  QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
  addLibraryPath("platforms");

  // 统一注册类型
  qRegisterMetaType<UI::PageMenu>("PageMenu");

  // 字体
  FontManager fm;
  fm.loadFonts();

  // 延时器
  _delayCaller = std::make_unique<DelayedCallTimer>();

  // 设置
  _settingManager = std::make_unique<SettingManager>(this);

  connect(this, &QApplication::aboutToQuit, this, &Application::cleanup);

  _session = std::make_unique<ok::session::AuthSession>(this);
}

Application *Application::Instance() {
  return qobject_cast<Application *>(qApp);
}

void Application::start() {

  // if (!session()->authenticated()) {
  this->createLoginUI();
  // } else {
  //   this->startMainUI();
  // }
  // nexus->start();
}

void Application::createLoginUI() {
  m_loginWindow = std::make_unique<UI::window::LoginWindow>();
  connect(m_loginWindow.get(), &UI::window::LoginWindow::loginResult,
          [&](ok::session::SignInInfo &signInInfo,
              ok::session::LoginResult &result) {
            if (result.status == ok::session::Status::SUCCESS) {
              onLoginSuccess(signInInfo);
            }
          });

  m_loginWindow->show();
}
void Application::deleteLoginUI() {
  disconnect(m_loginWindow.get());
  //  disconnect(this, &Application::createProfileFailed, //
  //             m_loginWindow.get(), &LoginWindow::onProfileLoadFailed);
  m_loginWindow.reset();
}

void Application::closeLoginUI() {
  // 关闭login窗口
  deleteLoginUI();
}

void Application::onLoginSuccess(ok::session::SignInInfo &signInInfo) {
  DEBUG_LOG(qsl("onLoginSuccess account:%1").arg(signInInfo.account));
  m_signInInfo = signInInfo;

  // 初始化 IM 模块
  initModuleIM(signInInfo);

  // 初始化 Painter 模块
#ifdef OK_MODULE_PAINTER
  initModulePainter();
#endif

  // 初始化截屏模块
  initScreenCaptor();

  // 启动主界面
  startMainUI();

#ifdef OK_PLUGIN
  // 初始化插件平台
  initPluginManager();
#endif
  // 关闭登录界面
  closeLoginUI();
}

void Application::startMainUI() {
  this->loadService();

  m_windowManager = UI::WindowManager::Instance();
  connect(m_windowManager, &WindowManager::menuPushed, this,
          &Application::onMenuPushed);

  connect(m_windowManager, &WindowManager::mainClose, [&](SavedInfo savedInfo) {
    for (auto m : m_moduleMap) {
      m->onSave(savedInfo);
    }

  });

  m_windowManager->startMainUI();
}

void Application::stopMainUI() {
  m_windowManager->stopMainUI();
  delete m_windowManager;
  m_windowManager = nullptr;
}

void Application::loadService() {}

void Application::initScreenCaptor() {
  //  DEBUG_LOG(("initScreenCaptor ..."));
  //  auto _screenCaptor = new OEScreenshot();
  //  m_moduleMap.insert(_screenCaptor->name(), _screenCaptor);
  //  DEBUG_LOG(("initScreenCaptor finished"));
}

void Application::cleanup() {
  DEBUG_LOG(("Cleanup..."));
  for (auto e : m_moduleMap) {
    e->cleanup();
  }
}

void Application::finish() {}

void Application::onMenuPushed(PageMenu menu, bool checked) {
  DEBUG_LOG(("menu:%1 checked:%2").arg((int)menu).arg(checked));

  switch (menu) {
  case UI::PageMenu::chat: {
    Module *m = m_moduleMap.value(Nexus::Name());
    if (checked) {
      if (!m->isStarted()) {
        auto container = m_windowManager->getContainer(menu);
        m->start(m_signInInfo, container);
      }
    }
    break;
  }
  }
}

void Application::onMenuReleased(PageMenu menu, bool checked) {}

void Application::initModuleIM(ok::session::SignInInfo &signInInfo) {
  DEBUG_LOG(("IM..."))

  auto im = Nexus::Create();

  //  connect(im, &Module::createProfileFailed, //
  //          m_loginWindow.get(), &LoginWindow::onProfileLoadFailed);

  //  Module &nexus = Nexus::getInstance();
  //  nexus.init(static_cast<Profile *>(profile));

  connect(static_cast<Nexus *>(im), &Nexus::updateAvatar, this,
          &Application::onAvatar);

  m_moduleMap.insert(im->name(), im);
}

#ifdef OK_PLUGIN
void Application::initPluginManager() {
  ok::plugin::PluginManager *pm = ok::plugin::PluginManager::instance();
  QStringList plugins = pm->availablePlugins();
  for (const QString &plugin : plugins) {
    qDebug() << "load plugin:" << plugin;
  }
}
#endif

void Application::onAvatar(const QPixmap &pixmap) {
  auto menu = m_windowManager->getMainMenu();
  if (!menu)
    return;

  menu->setAvatar(pixmap);
}

#ifdef OK_MODULE_PAINTER
void Application::initModulePainter() {
  auto p = Painter::Create();
  qDebug() << "painter:" << p;
}
#endif

} // namespace core
