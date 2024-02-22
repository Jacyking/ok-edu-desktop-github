#include "PluginInfoForm.h"

#include "base/files.h"
#include "lib/plugin/pluginhost.h"
#include "lib/network/NetworkHttp.h"
#include "lib/settings/OkSettings.h"
#include "ui_PluginInfoForm.h"
#include <QDebug>

namespace ok {
namespace plugin {

QString makePath(const QString &id, const QString &name) {
  return QString("%1/%2_%3").arg(ok::base::OkSettings::downloadDir(), id, name);
}

QString makePluginPath(const QString &name) {
  return QString("%1/%2").arg(ok::base::OkSettings::pluginDir(), name);
}

PluginInfoForm::PluginInfoForm(PluginInfo &info, QWidget *parent)
    : QWidget(parent), ui(new Ui::PluginInfoForm),
      pluginManager(PluginManager::instance()), id(info.id), mPluginInfo(info),
      downUrl(info.downUrl), mDownloaded(false) {

  ui->setupUi(this);
  ui->progressBar->setValue(0);
  ui->name->setText(info.name);
  ui->version->setText(info.version);
  ui->home->setText(info.homeUrl);
  ui->intro->setText(info.content);
  ui->installBtn->setText(tr("Install"));
  ui->progressBar->hide();

  qDebug() << "Display plugin" << info.shortName;

  if (pluginManager->isAvailable(info.shortName)) {
    setInstalled();
  }

  for (const auto &dir : pluginManager->pluginDirs()) {
    qDebug() << "PluginDir:" << dir;
  };

  connect(this, &PluginInfoForm::downloadFinished, [&](const QString &path) {
    QMutexLocker ml{&mMutex};
    http.reset();

    auto installed = pluginManager->installPlugin(path, mPluginInfo.fileName);
    if (installed)
      setInstalled();
  });
}

PluginInfoForm::~PluginInfoForm() { delete ui; }

void PluginInfoForm::on_installBtn_released() {
  QMutexLocker ml{&mMutex};
  if (mDownloaded) {
    qDebug() << "Is downloaded, will to uninstall the plugin.";
    toUninstall();
  } else {
    qDebug() << "Is not downloaded, will to install the plugin.";
    toInstall();
  }
}

void PluginInfoForm::toUninstall() {
  qDebug() << "To uninstall:" << mPluginInfo.shortName;
  setUninstalling();

  auto uninstallPlugin = pluginManager->uninstallPlugin(mPluginInfo.shortName);
  qDebug() << "To uninstall:" << mPluginInfo.shortName << "=>"
           << uninstallPlugin;

  if (uninstallPlugin)
    setUninstalled();
}

void PluginInfoForm::toInstall() {
  qDebug() << "To install:" << mPluginInfo.shortName;

  if (http.get()) {
    qWarning() << "Is downloading...";
    return;
  }

  qDebug() << "download=>" << downUrl;
  http = std::make_unique<network::NetworkHttp>();
  http->get(
      downUrl,
      [&](QByteArray buf, const QString &fileName) {
        auto path = makePath(id, fileName);
        qDebug() << "download bytes" << buf.size() << "be saved to=>" << path;
        if (!::base::Files::writeTo(buf, path)) {
          qWarning() << "Cannot to write plugin files." << path;
          return;
        }
        emit downloadFinished(path);
      },
      [&](qint64 bytesReceived, qint64 bytesTotal) {
        qDebug() << "Received bytes:" << bytesReceived << "/" << bytesTotal;
        ui->progressBar->setMaximum(bytesTotal);
        ui->progressBar->setValue(bytesReceived);
      });
  setInstalling();
}

void PluginInfoForm::setInstalled() {
  mDownloaded = true;
  ui->progressBar->hide();
  ui->installBtn->setText(tr("Uninstall"));
}

void PluginInfoForm::setUninstalled() {
  mDownloaded = false;
  ui->progressBar->hide();
  ui->installBtn->setText(tr("Install"));
}

void PluginInfoForm::setInstalling() {
  mDownloaded = false;
  ui->progressBar->show();
  ui->installBtn->setText(tr("Installing"));
}

void PluginInfoForm::setUninstalling() {
  mDownloaded = false;
  ui->progressBar->show();
  ui->installBtn->setText(tr("Uninstalling"));
}

} // namespace plugin
} // namespace ok