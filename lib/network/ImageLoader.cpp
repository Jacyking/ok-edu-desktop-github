
#include "ImageLoader.h"

#include <QObject>
#include <QPixmap>
#include <QString>
#include <QUrl>
#include <QtGui/QtGui>
#include <memory>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <base/basic_types.h>

#include <lib/network/backend/UserService.h>
#include <lib/network/backend/domain/UserInfo.h>

namespace utils {

using namespace ok::backend;

ImageLoader::ImageLoader(QObject *parent) : QObject(parent) {}

ImageLoader::~ImageLoader() {}

void ImageLoader::load(const QString &url, Fn<void(const QByteArray &)> fn) {

  QNetworkAccessManager manager;
  QEventLoop loop;

  QNetworkReply *reply = manager.get(QNetworkRequest(url));
  QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  fn(reply->readAll());
}


} // namespace utils
