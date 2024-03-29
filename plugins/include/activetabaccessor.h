#ifndef ACTIVETABACCESSOR_H
#define ACTIVETABACCESSOR_H

#include <QtPlugin>

class ActiveTabAccessingHost;

class ActiveTabAccessor {
public:
    virtual ~ActiveTabAccessor() { }

    virtual void setActiveTabAccessingHost(ActiveTabAccessingHost *host) = 0;
};

Q_DECLARE_INTERFACE(ActiveTabAccessor, "org.okstar.msg.ActiveTabAccessor/0.1");

#endif // ACTIVETABACCESSOR_H
