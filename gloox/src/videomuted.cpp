#include "videomuted.h"

namespace gloox {

    VideoMuted::VideoMuted(const std::string &node)
            : StanzaExtension(ExtVideMuted), //
              m_node(node) {

    }

    VideoMuted::VideoMuted(const Tag *tag)
            : StanzaExtension(ExtVideMuted) {
        if (!tag || tag->name() != "query" || tag->xmlns() != XMLNS_DISCO_INFO)
            return;

        m_node = tag->findAttribute("node");

        const TagList &l = tag->children();
        TagList::const_iterator it = l.begin();
        for (; it != l.end(); ++it) {
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

    VideoMuted::VideoMuted(const VideoMuted &devices)
            : StanzaExtension(ExtVideMuted), m_node(devices.m_node) {
    }

    VideoMuted::VideoMuted(bool muted) : StanzaExtension(ExtVideMuted) {
        m_muted = muted;
    }

    VideoMuted::~VideoMuted() {

    }

    const std::string &VideoMuted::filterString() const {
        static const std::string filter = "/iq/query[@xmlns='" + JITSI_VIDEO_MUTED + "']";
        return filter;
    }

    Tag *VideoMuted::tag() const {
        Tag *t = new Tag("videomuted", XMLNS, JITSI_VIDEO_MUTED);
        t->setCData(m_muted ? "true" : "false");
        return t;
    }
}
