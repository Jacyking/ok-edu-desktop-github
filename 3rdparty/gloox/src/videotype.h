#ifndef VIDEO_TYPE_H
#define VIDEO_TYPE_H

#include <string>
#include "gloox.h"
#include "tag.h"
#include "stanzaextension.h"

namespace gloox
{

    class GLOOX_API VideoType : public StanzaExtension
    {
    private:
        std::string m_node;
        std::string _type;

    public:
        VideoType(const std::string &node = EmptyString);
        VideoType(const Tag *tag);
        VideoType(const VideoType &devices);
        ~VideoType();

        // reimplemented from StanzaExtension
        virtual const std::string &filterString() const;

        // reimplemented from StanzaExtension
        virtual StanzaExtension *newInstance(const Tag *tag) const
        {
            return new VideoType(tag);
        }

        virtual StanzaExtension *clone() const
        {
            return new VideoType(*this);
        }

        virtual Tag *tag() const;
        const std::string &type() const;
    };
}
#endif
