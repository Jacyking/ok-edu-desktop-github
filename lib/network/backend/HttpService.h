#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <base/basic_types.h>
#include <base/logs.h>
#include <map>
#include <memory>
#include <lib/network/backend/BaseService.h>
#include <string>

namespace ok::backend {

typedef struct {
  bool success;
  QString url;
  QString key;
  QString contentType;
  QString extension;
  QString name;
} FileResult;

class HttpService : BaseService {
public:
  HttpService(QObject *parent = nullptr);
  ~HttpService();

  bool request(QString &baseUrl, QMap<QString, QString> &params,
               Fn<void(QJsonObject)> callback);
};

} // namespace ok::backend