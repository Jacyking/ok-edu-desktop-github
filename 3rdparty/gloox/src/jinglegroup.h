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

#ifndef GLOOX_JINGLEGROUP_H
#define GLOOX_JINGLEGROUP_H

#include "jingleplugin.h"

namespace gloox {

class Tag;

namespace Jingle {
/**
 * @brief An implementation of Jingle Grouping Framework (@xep{0338}) as a
 * StanzaExtension.
 *
 * @author Gao Jie <412555203@qq.com>
 * @since 1.0
 */
class Group : public Plugin {
public:
  //  enum Semantics { bundle, ls, semantics };
  typedef std::string Semantics;
  struct Content {
    std::string name;
  };
  typedef std::list<Content> ContentList;

  Group(Semantics semantics, const ContentList &contentList);
  Group(const Tag *tag = 0);

  Semantics getSemantics();

  ContentList contents();

  // reimplemented from Plugin
  virtual const StringList features() const;

  // reimplemented from Plugin
  virtual const std::string &filterString() const;

  // reimplemented from Plugin
  virtual Tag *tag() const;

  // reimplemented from Plugin
  virtual Plugin *newInstance(const Tag *tag) const;

  // reimplemented from Plugin
  virtual Plugin* clone() const
  {
    return new Group( *this );
  }

private:
  Semantics m_semantics;
  ContentList m_contents;
};

} // namespace Jingle
} // namespace gloox

#endif // GLOOX_JINGLEGROUP_H
