#ifndef SMARTBOARDDRAW_H
#define SMARTBOARDDRAW_H

#include <string>
#include <map>

//#include <gloox/tag.h>
//#include <gloox/personaleventingprotocolfilter.h>

#include "smartboard.h"
#include "smartboarddrawline.h"

namespace gloox{
class Plugin;
class Tag;
class PersonalEventingProtocolFilter;
}

namespace SmartBoard
{
   
    using Style = std::map<std::string, std::string> ;

    class SmartBoardDraw : public ITag
    {
        std::string _id;
        std::map<DrawType, DrawItem *> _plugins;
        Style _style;
        Point _point;
        Position _position;
    

    public:
        SmartBoardDraw();
        SmartBoardDraw(const gloox::Tag*, const gloox::PersonalEventingProtocolFilter* filter);

        const std::string &id() const;
        
        Style &style() ;

        const Point& point() const;


        const Position& position() const;
        void setPosition(const Position&);

        template <typename _DrawItem>
        const _DrawItem *findPlugin(DrawType type)
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
                return (_DrawItem *)(it->second);
            }
        }

        template <typename _DrawItem>
        void addPlugin(_DrawItem *drawItem)
        {
            _plugins.insert(std::make_pair(drawItem->type(), dynamic_cast<DrawItem *>(drawItem)));
        }
    };

    // end of SmartBoard
}
#endif // SMARTBOARDDRAW_H
