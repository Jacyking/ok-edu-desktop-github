#ifndef CONTACTINFOACCESSOR_H
#define CONTACTINFOACCESSOR_H

#include <QtPlugin>

class ContactInfoAccessingHost;

class ContactInfoAccessor {
public:
    virtual ~ContactInfoAccessor() { }

    virtual void setContactInfoAccessingHost(ContactInfoAccessingHost *host) = 0;
};

Q_DECLARE_INTERFACE(ContactInfoAccessor, "org.okstar.msg.ContactInfoAccessor/0.1");

#endif // CONTACTINFOACCESSOR_H
