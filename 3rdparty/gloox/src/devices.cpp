#include "devices.h"

namespace gloox
{

    Devices::Devices(const std::string &node)
        : StanzaExtension(ExtDevices), m_node(node)
    {
    }
    Devices::Devices(const Tag *tag)
        : StanzaExtension(ExtDevices)
    {
        if (!tag || tag->name() != "query" || tag->xmlns() != XMLNS_DISCO_INFO)
            return;

        m_node = tag->findAttribute("node");

        const TagList &l = tag->children();

        for (TagList::const_iterator it = l.begin(); it != l.end(); ++it)
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

    Devices::Devices(const Devices &devices)
        : StanzaExtension(ExtDevices), m_node(devices.m_node)
    {
    }

    Devices::Devices(const bool &audio, const bool &video)
        : StanzaExtension(ExtDevices), _audio(audio), _video(audio)
    {
    }
    
    Devices::~Devices()
    {
        // todo clean
    }

    const std::string &Devices::filterString() const
    {
        static const std::string filter = "/iq/query[@xmlns='" + JITSI_DEVICES + "']";
        return filter;
    }

    Tag *Devices::tag() const
    {
        Tag *t = new Tag("devices", XMLNS, JITSI_DEVICES);
        // TODO

        return t;
    }
    const bool &Devices::audio() const
    {
        return _audio;
    }

    const bool &Devices::video() const
    {
        return _video;
    }
}
