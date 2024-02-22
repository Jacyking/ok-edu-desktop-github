#include "LoginManager.h"
#include <array>
#include <base/logs.h>
#include "LoginJwt.h"

namespace login
{

    LoginManager::LoginManager(/* args */)
    {
        _logins.push_back((std::unique_ptr<Login>(new LoginJwt())));
    }

    LoginManager::~LoginManager()
    {
    }

    void LoginManager::login(const Account &account)
    {
        // DEBUG_LOG(("login:%1").arg(account.username));
    }

    void LoginManager::interrupt()
    {

    }

    network::CONNECT_STATUS LoginManager::status() const
    {
        return _status;
    }
}