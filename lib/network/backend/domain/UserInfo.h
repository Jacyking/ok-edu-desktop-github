#pragma once

#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QVariant>

#include <base/jsons.h>
#include <base/qbasic_types.h>

#include "../User.h"

namespace ok::backend {

enum class UserType {
  NONE = 0,
  Member = 1,
  Teacher = 2,
};

class UserInfo   {
public:
  explicit UserInfo() {}

  explicit UserInfo(const UserInfo &info)
      : id(info.id), userType(info.userType), uin(info.uin),
        name(info.name), username(info.username), avatar(info.avatar) {}

  virtual ~UserInfo() {}

  int64 getId() const { return id; }

  const QString &getUin() const { return uin; }

  const QString &getUsername() const { return username; }

  const QString &getName() const { return name; }

  const QString &getAvatar() const { return avatar; }

  int getUserType() const { return userType; }

private:
  int64 id = 0;
  int userType = -1;
  QString uin;
  QString name;
  QString username;
  QString avatar;
};

} // namespace ok::backend
