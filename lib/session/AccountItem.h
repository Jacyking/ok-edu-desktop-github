#pragma once

#include <QObject>

namespace ok {
namespace session{

class AccountItem {
public:
  AccountItem(const QString &username,
              const QString &password);

  //账号
  const QString &username;
  //密码
  const QString &password;
};
}

} // namespace session