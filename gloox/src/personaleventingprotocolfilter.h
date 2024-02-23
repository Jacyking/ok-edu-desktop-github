#ifndef PERSONAL_EVENTING_PROTOCL_FILTER_H_
#define PERSONAL_EVENTING_PROTOCL_FILTER_H_

#include "messagefilter.h"
#include "gloox.h"
#include "okplugin.h"

namespace gloox {
    class PersonalEventingProtocolFilter : public MessageFilter
    {
    private:
        /* data */
        int i;

    public:
        PersonalEventingProtocolFilter(MessageSession *parent);
        ~PersonalEventingProtocolFilter();

        void registerPlugin(Plugin *plugin);
        void filter(Message &msg);
        void decorate(Message &msg);
        void attachTo(MessageSession *session);
    };
}
#endif
