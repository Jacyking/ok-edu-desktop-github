#ifndef PLUGINITEMFORM_H
#define PLUGINITEMFORM_H

#include "base/timer.h"
#include "lib/plugin/PluginInfo.h"
#include <QWidget>

namespace Ui {
class PluginItemForm;
}
namespace network {
class NetworkHttp;
}
using namespace ok::plugin;

class PluginItemForm : public QWidget {
  Q_OBJECT
public:
  explicit PluginItemForm(int row, ok::plugin::PluginInfo &pluginInfo,
                          QWidget *parent = nullptr);
  ~PluginItemForm();
  void timesUp();
  void setLogo(const QImage& pixmap);


private:

  Ui::PluginItemForm *ui;
  PluginInfo info;
  int row;
  std::unique_ptr<network::NetworkHttp> http;

signals:
  void loadLogo();
  void logoDownloaded(const QString &fileName, QByteArray &img);


public slots:
  void onLogoDownloaded(const QString &fileName, QByteArray &img);
};

#endif // PLUGINITEMFORM_H
