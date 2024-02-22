#pragma once

#include <QApplication>
#include <QStringList>
#include <memory>

namespace core {

class Application;

class Launcher {

public:
  static std::unique_ptr<Launcher> Create(int argc, char *argv[]);

  Launcher(int argc, char *argv[]);


  int startup();

  int shutdown();

private:
  int executeApplication();

  int _argc;
  char **_argv;
  Application *app;
  QStringList _arguments;
};
} // namespace core
