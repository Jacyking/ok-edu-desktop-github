#ifndef USER_AGENT_H__
#define USER_AGENT_H_

#include "gloox.h"
#include "stanzaextension.h"

namespace gloox {

class GLOOX_API UserAgent : public StanzaExtension {
private:
  /* data */
  std::string m_node;

public:
  UserAgent(const std::string &node = EmptyString);
  UserAgent(const Tag *tag);
  UserAgent(const UserAgent &userAgent);
  ~UserAgent();

  virtual const std::string &filterString() const;

  virtual StanzaExtension *newInstance(const Tag *tag) const {
    return new UserAgent(tag);
  }

  virtual StanzaExtension *clone() const { return new UserAgent(*this); }

  virtual Tag *tag() const;
};

} // namespace gloox
#endif