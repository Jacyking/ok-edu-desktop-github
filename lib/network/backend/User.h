#pragma once

#include <map>

#include "base/OkAccount.h"
#include <QString>
#include <base/basic_types.h>
#include <string>

namespace ok::backend {
// TODO
//struct UserJID {
//  QString id;
//  QString from;
//  QString nickname;
//  bool operator==(const UserJID &b) const { return this->id == b.id; }
//};
//
//typedef std::map<PeerUIN, backend::UserJID> UserJIDMap;

struct PeerStatus {
  bool audioMuted = true;
  bool videoMuted = true;
  bool raisedHand = false;
  std::string videoType;
};

/**
 *
 */
class UserId {
public:
  UserId() = default;

  UserId(std::string jid,
         std::string name,
         std::string nick="");

  const std::string& getJid() const;
  const std::string& getUsername() const;
  const std::string& getNick() const;

private:
  std::string jid;
  std::string username;
  std::string nick;
};

} // namespace ok::backend
