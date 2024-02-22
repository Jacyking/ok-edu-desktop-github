#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>
#include <memory>
#include <string>

#include <base/basic_types.h>

#include <lib/network/backend/BaseService.h>
#include <lib/session/AuthSession.h>

namespace ok::backend {

using namespace ok::session;

class SysAccount {
public:
  quint64 id;
  QString iso;
  QString name;
  QString username;
  QString nickname;

  SysAccount(const QJsonObject &data) {
    /**
     * {
     * "id":2001,
     * "iso":"CN",
     * "username":"On1qv1AfQmap",
     * "nickname":"OkStar",
     * "firstName":"",
     * "lastName":"",
     * "no":null,
     * "avatar":"/assets/images/avatar.jpg",
     * "name":"OkStar"
     * }
     */
    id = data.value("id").toVariant().toULongLong(); //
    iso = data.value("iso").toString();              //
    name = data.value("name").toString();            //
    username = data.value("username").toString();    //
    nickname = data.value("nickname").toString();    //
  }

  QString toString() {
    return QString("{id:%1, username:%2, name:%3, nickname:%4 iso:%5}") //
        .arg(QString::number(id), username, name, nickname, iso);
  }
};

class PassportService : BaseService {
  Q_OBJECT
public:
  PassportService(QObject *parent = nullptr);
  ~PassportService();

  bool getAccount(const QString &account, Fn<void(Res<SysAccount> &)> fn);
};
} // namespace ok::backend
