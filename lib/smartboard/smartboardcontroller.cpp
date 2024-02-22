#include "smartboardcontroller.h"
namespace SmartBoard
{
    Controller::Controller(const std::string & id)
    {
        _id = id;
    }

    const UserList& Controller::userList( ) const{
        return _userList;
    }
}
