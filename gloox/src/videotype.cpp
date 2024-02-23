#include "videotype.h"

namespace gloox
{

    VideoType::VideoType(const std::string &node)
        : StanzaExtension(ExtVideoType), m_node(node)
    {
    }
    VideoType::VideoType(const Tag *tag)
        : StanzaExtension(ExtVideoType)
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

    VideoType::VideoType(const VideoType &devices)
        : StanzaExtension(ExtVideoType), m_node(devices.m_node)
    {
    }

    VideoType::~VideoType()
    {
        // todo clean
    }

    const std::string &VideoType::filterString() const
    {
        static const std::string filter = "/iq/query[@xmlns='" + JITSI_VIDEO_TYPE + "']";
        return filter;
    }

    Tag *VideoType::tag() const
    {
        Tag *t = new Tag("videotype", XMLNS, JITSI_VIDEO_TYPE);
        // TODO

        return t;
    }
    
    const std::string &VideoType::type() const
    {
        return _type;
    }

}
