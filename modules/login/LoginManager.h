#pragma once

#include "Login.h"
#include "lib/network/network.h"
#include <memory>
#include <vector>


namespace login {

typedef struct {
  LoginType type;
  std::string &username;
  std::string &password;
} Account;

class LoginManager {
private:
  /* 登录器 */
  std::vector<std::unique_ptr<Login>> _logins;
  //        network::CONNECT_STATUS _status = network::CONNECT_STATUS::NONE;

public:
  LoginManager(/* args */);
  ~LoginManager();

  void login(const Account &);

  void interrupt();

};
} // namespace login