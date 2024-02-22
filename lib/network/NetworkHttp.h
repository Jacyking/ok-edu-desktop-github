#pragma once

#include <QByteArray>
#include <QFile>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QUrl>
#include <memory>

#include <base/basic_types.h>
#include <base/timer.h>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkCookie;

namespace network {

class NetworkHttp : public QObject {
  Q_OBJECT

public:
  explicit NetworkHttp(QObject *parent = nullptr);
  ~NetworkHttp() override;

  void httpFinished();

  void wrapRequest(const QNetworkRequest &request, const QUrl &url);

  void
  get(const QUrl &url,                                                      //
      Fn<void(QByteArray body, const QString filename)> fn,                 //
      Fn<void(qint64 bytesReceived, qint64 bytesTotal)> progress = nullptr, //
      Fn<void(const QString errStr)> failed = nullptr);

  QByteArray get(const QUrl &url,
                 const Fn<void(qint64 bytesReceived, qint64 bytesTotal)>
                     &downloadProgress = nullptr);

  void getJSON(const QUrl &url, Fn<void(QJsonDocument)> fn,
               Fn<void(QString)> err= nullptr);

  void post(const QUrl &url, const QString &str, Fn<void(QByteArray)> fn);

  QByteArray post(const QUrl &url, const QString &str);

  void postJSON(const QUrl &url, const QJsonObject &data,
                Fn<void(const QJsonDocument &)> fn);

  void postJSON(const QUrl &url, const QString &data,
                Fn<void(const QJsonDocument &)> fn);

  void PostFormData(const QUrl &url, QFile *file,
                    Fn<void(int bytesSent, int bytesTotal)> uploadProgress,
                    Fn<void(const QJsonObject &json)> readyRead);

  virtual void PostFormData(const QUrl &url, const QByteArray &byteArray,
                            const QString &contentType, const QString &filename,
                            Fn<void(int, int)> uploadProgress,
                            Fn<void(const QJsonObject &)> readyRead);

  virtual void openUrl(const QUrl &url);

protected:
  std::unique_ptr<QNetworkAccessManager> _manager;
  QList<QNetworkCookie> _cookies;
};
} // namespace network
