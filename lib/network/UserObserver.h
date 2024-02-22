#pragma once

namespace network {

class UserObserver {
public:
//   virtual UserObserver() = 0;
//   virtual ~UserObserver() = 0;

  virtual void onLogin() = 0;
  virtual void onLogout() = 0;
};

} // namespace network
