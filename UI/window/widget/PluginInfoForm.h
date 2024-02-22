#ifndef PLUGININFOFORM_H
#define PLUGININFOFORM_H

#include "lib/plugin/PluginInfo.h"
#include "lib/plugin/pluginmanager.h"
#include <QRecursiveMutex>
#include <QWidget>

namespace Ui {
class PluginInfoForm;
}

namespace network {
class NetworkHttp;
}

namespace ok {
namespace plugin {

class PluginInfoForm : public QWidget {
  Q_OBJECT

public:
  explicit PluginInfoForm(PluginInfo &info, QWidget *parent = nullptr);
  ~PluginInfoForm();

  const QString &pluginId() const { return id; }
  void setInstalling();
  void setInstalled();
  void setUninstalling();
  void setUninstalled();

  void toInstall();
  void toUninstall();

private:
  Ui::PluginInfoForm *ui;
  PluginManager *pluginManager;
  QString id;
  PluginInfo mPluginInfo;
  QString downUrl;
  std::unique_ptr<network::NetworkHttp> http;
  QRecursiveMutex mMutex;

  bool mDownloaded;

signals:
  void downloadFinished(const QString& path);
  

private slots:
  void on_installBtn_released();
  
};
} // namespace plugin
} // namespace ok
#endif // PLUGININFOFORM_H
