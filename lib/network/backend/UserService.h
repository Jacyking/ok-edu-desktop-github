#pragma once

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <base/basic_types.h>

#include <lib/network/backend/BaseService.h>
#include <lib/network/backend/HttpService.h>
#include <lib/network/backend/domain/AuthInfo.h>


#include "lib/network/NetworkManager.h"
#include "lib/session/AuthSession.h"

namespace ok::backend {

struct OrgStaff {

  QString no;
  QString name;
  QString phone;
  QString email;
  QString username;

  OrgStaff(const QJsonObject &data) {
    no = data.value("no").toString();             //
    email = data.value("email").toString();       //
    name = data.value("name").toString();         //
    username = data.value("username").toString(); //
    phone = data.value("phone").toString();       //
  }

  QString toString() {
    return QString("{no:%1, username:%2, name:%3, phone:%4 email:%5}") //
        .arg(no, username, name, phone, email);
  }
};

class UserService : public BaseService {
  Q_OBJECT
public:
  UserService(QObject *parent = nullptr);
  ~UserService();

  void search(const QString &query,
              Fn<void(const QList<OrgStaff*> &)> callback);

  void setUserType(const QString &userType);
};

} // namespace ok::backend
