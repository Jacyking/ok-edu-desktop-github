#ifndef SMARTBOARDCONTROLLER_H
#define SMARTBOARDCONTROLLER_H

#include "smartboard.h"
//#include <gloox/tag.h>
//#include <gloox/personaleventingprotocolfilter.h>

namespace gloox{
class Plugin;
class Tag;
class PersonalEventingProtocolFilter;
}

namespace SmartBoard
{

    class Controller : public ITag
    {
        private:
            std::string _id;
            UserList _userList;
            ControllerMap _plugins;

        public:
            Controller(const std::string &);
            Controller(const gloox::Tag*, const gloox::PersonalEventingProtocolFilter* filter);

            const UserList &userList() const;

            template <typename _ControllerItem>
            const _ControllerItem *findPlugin(ControllerType type)
            {
                auto it = _plugins.find(type);
                if (it == _plugins.end())
                {
                    //没找到
                    return nullptr;
                }
                else
                {
                    //找到
                    return (_ControllerItem *)(it->second);
                }
            }

            template <typename _ControllerItem>
            void addPlugin(_ControllerItem *drawItem)
            {
                _plugins.insert(std::make_pair(drawItem->type(), dynamic_cast<ControllerItem *>(drawItem)));
            }
    };
}
#endif // SMARTBOARDCONTROLLER_H
