#ifndef VIDEO_MUTED_H
#define VIDEO_MUTED_H

#include "gloox.h"
#include "stanzaextension.h"
#include "tag.h"
#include <string>

namespace gloox {

class GLOOX_API VideoMuted : public StanzaExtension {

public:
  VideoMuted(const std::string &node = EmptyString);
  VideoMuted(const Tag *tag);
  VideoMuted(const VideoMuted &devices);
  VideoMuted(bool muted);
  ~VideoMuted();

  // reimplemented from StanzaExtension
  virtual const std::string &filterString() const;

  // reimplemented from StanzaExtension
  virtual StanzaExtension *newInstance(const Tag *tag) const {
    return new VideoMuted(tag);
  }

  virtual StanzaExtension *clone() const { return new VideoMuted(*this); }

  virtual Tag *tag() const;
  bool muted() const { return m_muted; };

private:
  std::string m_node;
  bool m_muted;
};
} // namespace gloox
#endif // DEVICES_H
