#include "useragent.h"

namespace gloox {

UserAgent::UserAgent(const std::string &node)
    : StanzaExtension(ExtUserAgent), m_node(node) {}
UserAgent::UserAgent(const Tag *tag) : StanzaExtension(ExtUserAgent) {
  // if (!tag || tag->name() != "query" || tag->xmlns() != XMLNS_DISCO_INFO)
  //     return;

  // m_node = tag->findAttribute("node");

  // const TagList &l = tag->children();
  // TagList::const_iterator it = l.begin();
  // for (; it != l.end(); ++it)
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

UserAgent::UserAgent(const UserAgent &devices)
    : StanzaExtension(ExtUserAgent), m_node(devices.m_node) {}

UserAgent::~UserAgent() {
  // todo clean
}
const std::string &UserAgent::filterString() const {
  static const std::string filter =
      "/iq/query[@xmlns='" + JITSI_USER_AGENT + "']";
  return filter;
}

Tag *UserAgent::tag() const {
  //   Tag *t = new Tag("user-agent", XMLNS, JITSI_USER_AGENT);
  // TODO

  return NULL;
}
} // namespace gloox
