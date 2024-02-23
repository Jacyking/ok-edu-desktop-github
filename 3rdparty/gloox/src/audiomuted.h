#ifndef AUDIO_MUTED_H
#define AUDIO_MUTED_H

#include <string>
#include "gloox.h"
#include "tag.h"
#include "stanzaextension.h"

namespace gloox
{

    class GLOOX_API AudioMuted : public StanzaExtension
    {
    private:
        std::string m_node;
        bool _muted;

    public:
        AudioMuted(const std::string &node = EmptyString);
        AudioMuted(const Tag *tag);
        AudioMuted(const AudioMuted &devices);
        AudioMuted(const bool &muted);
        ~AudioMuted();

        // reimplemented from StanzaExtension
        virtual const std::string &filterString() const;

        // reimplemented from StanzaExtension
        virtual StanzaExtension *newInstance(const Tag *tag) const
        {
            return new AudioMuted(tag);
        }

        virtual StanzaExtension *clone() const
        {
            return new AudioMuted(*this);
        }

        virtual Tag *tag() const;
        const bool &muted() const;
    };
}
#endif // DEVICES_H
