#include "User.h"

#include <utility>

namespace ok::backend {

UserId::UserId(std::string jid_,  //
               std::string name_, //
               std::string nick_  )//
    : jid(std::move(jid_)),       //
      username(std::move(name_)), //
      nick(std::move(nick_))      //
{}

const std::string&UserId::getJid() const { return  (jid); }

const std::string&UserId::getUsername() const { return  (username); }

const std::string&UserId::getNick() const { return  (nick); }

} // namespace ok::backend