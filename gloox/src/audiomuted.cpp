#include "audiomuted.h"

namespace gloox
{

    AudioMuted::AudioMuted(const std::string &node)
        : StanzaExtension(ExtAudioMuted), m_node(node)
    {
    }
    AudioMuted::AudioMuted(const Tag *tag)
        : StanzaExtension(ExtAudioMuted)
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

    AudioMuted::AudioMuted(const AudioMuted &devices)
        : StanzaExtension(ExtAudioMuted), m_node(devices.m_node)
    {
    }

    AudioMuted::AudioMuted(const bool &muted) : StanzaExtension(ExtAudioMuted)
    {
        _muted = muted;
    }

    AudioMuted::~AudioMuted()
    {
        // todo clean
    }

    const std::string &AudioMuted::filterString() const
    {
        static const std::string filter = "/iq/query[@xmlns='" + JITSI_AUDIO_MUTED + "']";
        return filter;
    }

    Tag *AudioMuted::tag() const
    {
        Tag *t = new Tag("audiomuted", XMLNS, JITSI_AUDIO_MUTED);
        // TODO

        return t;
    }
    const bool &AudioMuted::muted() const
    {
        return _muted;
    }
 
}
