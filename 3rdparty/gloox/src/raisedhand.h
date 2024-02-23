#ifndef RAISEDHAND_H
#define RAISEDHAND_H

#include <string>
#include "gloox.h"
#include "tag.h"
#include "stanzaextension.h"

namespace gloox
{

    class GLOOX_API RaisedHand : public StanzaExtension
    {
    private:
        std::string m_node;
        bool _raised;

    public:
        RaisedHand(const std::string &node = EmptyString);
        RaisedHand(const Tag *tag);
        RaisedHand(const RaisedHand &devices);
        RaisedHand(const bool &raised);
        ~RaisedHand();

        virtual const std::string &filterString() const;

        virtual StanzaExtension *newInstance(const Tag *tag) const
        {
            return new RaisedHand(tag);
        }

        virtual StanzaExtension *clone() const
        {
            return new RaisedHand(*this);
        }

        virtual Tag *tag() const;
        const bool &raised() const;
    };
}
#endif