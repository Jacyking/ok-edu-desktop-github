#include "HttpService.h"

#include <map>

#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QMapIterator>
#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <memory>
#include <string>

#include <base/basic_types.h>
#include <base/logs.h>

#include "lib/network/NetworkManager.h"
#include <lib/network/backend/BaseService.h>

namespace ok::backend {

HttpService::HttpService(QObject *parent) : BaseService(parent) {}

HttpService::~HttpService() {}

bool HttpService::request(QString &_baseUrl, QMap<QString, QString> &params,
                          Fn<void(QJsonObject)> callback) {
  QUrl url(_baseUrl);

  if (0 < params.size()) {
    QUrlQuery uQuery(url.query());
    QMapIterator<QString, QString> iter(params);
    while (iter.hasNext()) {
      iter.next();
      uQuery.addQueryItem(iter.key(), iter.value());
    }
    url.setQuery(uQuery);
  }

  http->getJSON(url, [callback](QJsonDocument res) {
    if (res.object().value(("success")).toBool()) {
      QJsonObject jo = res.object().value("data").toObject();
      callback(jo);
    }
  });
  return true;
}
} // namespace ok::backend
