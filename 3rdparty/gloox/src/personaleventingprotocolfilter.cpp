#include "personaleventingprotocolfilter.h"

namespace gloox {

    PersonalEventingProtocolFilter::PersonalEventingProtocolFilter(MessageSession *parent)
        : MessageFilter(parent)
    {
    }

    PersonalEventingProtocolFilter::~PersonalEventingProtocolFilter()
    {
    
    }

    void PersonalEventingProtocolFilter::filter(Message &msg){

    }

    void PersonalEventingProtocolFilter::attachTo(MessageSession *session)
    {
    }

    /**
     * This function receives a message right before it is sent out (there may be other filters
     * which get to see the message after this filter, though).
     * @param msg The tag to decorate. It contains the message to be sent.
     */
    void PersonalEventingProtocolFilter::decorate(Message &msg)
    {
    }
}