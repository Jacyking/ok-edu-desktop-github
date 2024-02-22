#include "BookedService.h"
#include <QObject>
#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>

namespace ok::backend {

BookedService::BookedService(QObject *parent) : BaseService(parent) {}

BookedService::~BookedService() {}

bool BookedService::requestCurrent(Fn<void(BookedInfo)> callback) {
  QString url(_baseUrl + "/booked/current");
  return requestBooked(url, callback);
}

bool BookedService::requestNext(Fn<void(BookedInfo)> callback) {
  QString url(_baseUrl + "/booked/next.do");
  return requestBooked(url, callback);
}

bool BookedService::requestDowncount(Fn<void(DowncountInfo)> callback) {

  QString url(_baseUrl + "/booked/downcount.do");
  QMap<QString, QString> params;

  HttpService httpService;
  return httpService.request(url, params, [this, callback](QJsonObject res) {
    if (res.value(("success")).toBool()) {
      QJsonObject jo = res.value("data").toObject();
      DowncountInfo _bookedInfo;
//      _bookedInfo.fromJSON(jo);
      callback(_bookedInfo);
    }
  });
}

bool BookedService::requestBooked(QString &url, Fn<void(BookedInfo)> callback) {

  QMap<QString, QString> params;

  HttpService httpService;
  return httpService.request(url, params, [this, callback](QJsonObject res) {
    if (res.value(("success")).toBool()) {
      QJsonObject jo = res.value("data").toObject();
      BookedInfo _bookedInfo;
      _bookedInfo.fromJSON(jo);
      callback(_bookedInfo);
    }
  });
}

QString BookedService::baseUrl() { return this->_baseUrl; }
} // namespace ok::backend