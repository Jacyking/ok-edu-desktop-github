/**
 * Copyright (c) 2022 船山科技 chuanshantech.com
OkEDU-Classroom is licensed under Mulan PubL v2.
You can use this software according to the terms and conditions of the Mulan PubL v2.
You may obtain a copy of Mulan PubL v2 at:
         http://license.coscl.org.cn/MulanPubL-2.0
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PubL v2 for more details.
 */

#include "jinglegroup.h"
#include "tag.h"

namespace gloox {
namespace Jingle {

Group::Group(Semantics semantics, const ContentList &contentList)
    : Plugin(PluginGroup), m_semantics(semantics), m_contents(contentList) {
  //
}

Group::Group(const Tag *tag) : Plugin(PluginGroup) {
  if (!tag || tag->name() != "group" || tag->xmlns() != XMLNS_JINGLE_APPS_GROUP)
    return;
  m_semantics = tag->findAttribute("semantics");
  //  if (sem == "semantics") {
  //    m_semantics = Semantics::semantics;
  //  } else if (sem == "LS") {
  //    m_semantics = Semantics::ls;
  //  } else if (sem == "bundle") {
  //    m_semantics = Semantics::bundle;
  //  }

  TagList tagList = tag->findChildren("content");
  TagList::const_iterator it = tagList.begin();
  for (; it != tagList.end(); ++it) {
    Content content = {(*it)->findAttribute("name")};
    m_contents.push_back(content);
  }
}

Group::Semantics Group::getSemantics() { return m_semantics; }

Group::ContentList Group::contents() { return m_contents; }

const StringList Group::features() const {
  StringList sl;
  sl.push_back(XMLNS_JINGLE_APPS_GROUP);
  return sl;
}

const std::string &Group::filterString() const {
  static const std::string filter =
      "group[@xmlns='" + XMLNS_JINGLE_APPS_GROUP + "']";
  return filter;
}

Plugin *Group::newInstance(const Tag *tag) const { return new Group(tag); }
Tag *Group::tag() const {
  Tag *t = new Tag("group", XMLNS, XMLNS_JINGLE_APPS_GROUP);

  t->addAttribute("semantics", m_semantics);

  ContentList::const_iterator it = m_contents.begin();
  for (; it != m_contents.end(); ++it) {
    Tag *n = new Tag(t, "content");
    n->addAttribute("name", (*it).name);
  }
  return t;
}
} // namespace Jingle
} // namespace gloox