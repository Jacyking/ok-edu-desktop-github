#include "raisedhand.h"

namespace gloox
{

    RaisedHand::RaisedHand(const std::string &node)
        : StanzaExtension(ExtRaisedHand), m_node(node)
    {
    }
    RaisedHand::RaisedHand(const Tag *tag)
        : StanzaExtension(ExtRaisedHand)
    {
        if (!tag || tag->name() != "query" || tag->xmlns() != XMLNS_DISCO_INFO)
            return;

        m_node = tag->findAttribute("node");

        const TagList &l = tag->children();
        TagList::const_iterator it = l.begin();
        for (; it != l.end(); ++it)
        {
            // TODO
            // const std::string &name = (*it)->name();
            // if (name == "identity")
            //     m_identities.push_back(new Identity((*it)));
            // else if (name == "feature" && (*it)->hasAttribute("var"))
            //     m_features.push_back((*it)->findAttribute("var"));
            // else if (!m_form && name == "x" && (*it)->xmlns() == XMLNS_X_DATA)
            //     m_form = new DataForm((*it));
        }
    }

    RaisedHand::RaisedHand(const RaisedHand &devices)
        : StanzaExtension(ExtRaisedHand), m_node(devices.m_node)
    {
    }

    RaisedHand::RaisedHand(const bool &raised) : StanzaExtension(ExtRaisedHand)
    {
        _raised = raised;
    }

    RaisedHand::~RaisedHand()
    {
        // todo clean
    }

    const std::string &RaisedHand::filterString() const
    {
        static const std::string filter = "/iq/query[@xmlns='" + JITSI_DEVICES + "']";
        return filter;
    }

    Tag *RaisedHand::tag() const
    {
        Tag *t = new Tag("devices", XMLNS, JITSI_DEVICES);
        // TODO

        return t;
    }
    const bool &RaisedHand::raised() const
    {
        return _raised;
    }

  
}