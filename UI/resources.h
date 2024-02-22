#pragma once

#include <QString>

namespace utils {

#define QSS_CLASS "class"

// qss类型（resources.cpp一致）
enum class QSS {
  application, // application.qss
  login,       // login.qss
  menu,        // menu.qss
  toolbox,     // toolbox.qss
  IM,          // IM.qss
  topbar,      // topbar.qss
  titlebar,    // titlebar.qss
  setting,     // setting.qss
};

class Resources {
public:
  Resources();
  ~Resources();
  static QString loadQss(QSS qss);
};

} // namespace utils