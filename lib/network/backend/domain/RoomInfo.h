#pragma once

#include <QJsonObject>
#include <QObject>
#include <base/jsons.h>

namespace ok::backend {

class RoomInfo   {
public:
  QString getJid() { return jid; }
  QString getName() { return name; }
  QString getPassword() { return password; }
  QString getSn() { return sn; }

  inline void setJid(QString &_jid) { jid = _jid; }

  inline void setName(QString &_name) { name = _name; }

  inline void setPassword(QString &_password) { password = _password; }

private:
  QString jid;
  QString name;
  QString password;
  QString sn;
};

} // namespace ok::backend
