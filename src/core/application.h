#pragma once

#include <QApplication>
#include <QObject>
#include <memory>

#include <base/timer.h>

#include "UI/window/window/LoginWindow.h"
#include <UI/WindowManager.h>
#include <UI/core/ControllerManager.h>
#include <UI/core/SettingManager.h>
#include <UI/window/window/MainWindow.h>

#include "launcher.h"
#include "lib/network/NetworkManager.h"

#include "modules/module.h"

namespace ok {
namespace session {
class AuthSession;
}
} // namespace ok

namespace core {

using namespace network;
using namespace UI::window;

class Application : public QApplication {
  Q_OBJECT
public:
  Application(core::Launcher *launcher, int &argc, char **argv);

  static Application *Instance();

  void start();

  void finish();

  inline SettingManager *settingManager() { return _settingManager.get(); }

  inline ControllerManager *controllerManager() {
    return _controllerManager.get();
  }

protected:
  void initScreenCaptor();

  void initIM();

private:
  QMap<QString, Module *> m_moduleMap;

  void *profile = nullptr;

  int _argc;
  char **_argv;

  std::unique_ptr<ok::session::AuthSession> _session;

  std::unique_ptr<SettingManager> _settingManager;

  std::unique_ptr<ControllerManager> _controllerManager;

  std::unique_ptr<UI::window::LoginWindow> m_loginWindow;

  std::unique_ptr<base::DelayedCallTimer> _delayCaller;
  WindowManager *m_windowManager;
  ok::session::SignInInfo m_signInInfo;

  void loadService();

  void createLoginUI();
  void deleteLoginUI();
  void closeLoginUI();

  void startMainUI();
  void stopMainUI();

  void initModuleIM(ok::session::SignInInfo &signInInfo);

#ifdef OK_MODULE_PAINTER
  void initModulePainter();
#endif

#ifdef OK_PLUGIN
  void initPluginManager();
#endif

public slots:
  void cleanup();

  void onLoginSuccess(ok::session::SignInInfo &);

  void onMenuPushed(PageMenu menu, bool checked);
  void onMenuReleased(PageMenu menu, bool checked);

  void onAvatar(const QPixmap &);
};
} // namespace core
