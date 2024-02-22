#include "ChatService.h"

#include <QObject>
#include <QUrl>
#include <string>

#include "../backend/domain/RoomInfo.h"
#include "lib/network/NetworkManager.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>

namespace ok::backend {

ChatService::ChatService(QObject *parent) : BaseService(parent) {}

ChatService::~ChatService() {}

QString ChatService::current() {
  QUrl url(QString(_baseUrl + "/conference/current"));
  QJsonObject obj = Jsons::toJSON(http->get(url)).object();
  return obj.value("data").toString();
}
void ChatService::getRoomInfo(Fn<void(RoomInfo &)> callback) {
  QUrl url(QString(_baseUrl + "/conference/info"));
  http->getJSON(url, [&, callback](QJsonDocument res) {
    auto obj = res.object();
    if (obj.value("success").isNull() || !obj.value("success").toBool(false)) {
      return;
    }

    QJsonObject jo = obj.value("data").toObject();

//    RoomInfo info;
//    info.fromJSON(jo);
//    callback(info);
  });
}

void ChatService::listRoomInfos(Fn<void(std::list<RoomInfo> &)> callback) {

  QUrl url(QString(_baseUrl + "/conference/list"));
  http->getJSON(url, [&, callback](QJsonDocument doc) {
    auto res = doc.object();
    if (res.value("success").isNull() || !res.value("success").toBool(false)) {
      return;
    }

    QJsonArray list = res.value("data").toArray();
    std::list<RoomInfo> rooms;
    for (QJsonValue val : list) {
      auto obj = val.toObject();
//      RoomInfo info;
//      info.fromJSON(obj);
//      rooms.push_back(info);
    }
    callback(rooms);
  });
}

void ChatService::saveSn(const QString &sn, Fn<void(bool)> callback) {
  QUrl url(QString(_baseUrl + "/conference/save"));
  http->postJSON(url, (sn), [&](QJsonDocument doc) {
    auto res= doc.object();
    DEBUG_LOG_S(L_INFO) << "received:" << (res);
    if (res.value("success").isNull() || !res.value("success").toBool(false)) {
      return;
    }
    callback(true);
  });
}
} // namespace ok::backend
