#include "PluginItemForm.h"
#include "base/files.h"
#include "lib/network/NetworkHttp.h"
#include "ui_PluginItemForm.h"
#include <QTimer>
#include "base/images.h"

PluginItemForm::PluginItemForm(int row_, ok::plugin::PluginInfo &pluginInfo,
                               QWidget *parent)
    : QWidget(parent), ui(new Ui::PluginItemForm), info(pluginInfo), row(row_) {
  ui->setupUi(this);
  ui->name->setText(pluginInfo.name);
  ui->version->setText(pluginInfo.version);
  connect(this, &PluginItemForm::loadLogo, this, &PluginItemForm::timesUp);

  http = std::make_unique<network::NetworkHttp>();
  connect(this, &PluginItemForm::logoDownloaded, this,
          &PluginItemForm::onLogoDownloaded);
}

PluginItemForm::~PluginItemForm() {
  disconnect(this, &PluginItemForm::loadLogo, this, &PluginItemForm::timesUp);
  disconnect(this, &PluginItemForm::logoDownloaded, this,
             &PluginItemForm::onLogoDownloaded);
  delete ui;
}

void PluginItemForm::timesUp() {
  http->get(info.logoUrl, [&](QByteArray img, const QString &fileName) {
    Q_UNUSED(fileName);
    qDebug() << "渲染图片:" << fileName << img.size();
    emit logoDownloaded(fileName, img);

    QTimer::singleShot(100, this, [=, this]() { http.reset(); });
  });
}

void PluginItemForm::setLogo(const QImage &img) {
  ui->logoLabel->setPixmap(QPixmap::fromImage(img));
  ui->logoLabel->setScaledContents(true);
}

void PluginItemForm::onLogoDownloaded(const QString &fileName,
                                      QByteArray &img) {
  Q_UNUSED(fileName)
  QImage image;
  if (base::Images::putToImage(img, image)) {
    setLogo(image);
  }
}