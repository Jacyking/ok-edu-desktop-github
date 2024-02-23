#ifndef DEVICES_H
#define DEVICES_H

#include "gloox.h"
#include "stanzaextension.h"
#include "tag.h"
#include <string>

namespace gloox {

class GLOOX_API Devices : public StanzaExtension {
private:
  std::string m_node;
  bool _audio;
  bool _video;

public:
  Devices(const std::string &node = EmptyString);
  Devices(const Tag *tag);
  Devices(const Devices &devices);
  Devices(const bool &audio, const bool &video);
  ~Devices();

  virtual const std::string &filterString() const;

  virtual StanzaExtension *newInstance(const Tag *tag) const {
    return new Devices(tag);
  }

  virtual StanzaExtension *clone() const { return new Devices(*this); }

  virtual Tag *tag() const;
  const bool &audio() const;
  const bool &video() const;
};
} // namespace gloox
#endif // DEVICES_H
