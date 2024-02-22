#pragma once

#include <list>

#include <QObject>

#include "./domain/RoomInfo.h"
#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>


namespace ok::backend {

class ChatService : public BaseService {
  Q_OBJECT

public:
  ChatService(QObject *parent);
  ~ChatService();

  void getRoomInfo(Fn<void(RoomInfo &)> callback);
  QString current();

  void listRoomInfos(Fn<void(std::list<RoomInfo> &)> callback);

  void saveSn(const QString &sn, Fn<void(bool)> callback);
  };
} // namespace ok::backend
