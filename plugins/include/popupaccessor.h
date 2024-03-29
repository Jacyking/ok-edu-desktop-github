#ifndef POPUPACCESSOR_H
#define POPUPACCESSOR_H

#include <QtPlugin>

class PopupAccessingHost;

class PopupAccessor {
public:
    virtual ~PopupAccessor() { }

    virtual void setPopupAccessingHost(PopupAccessingHost *host) = 0;
};

Q_DECLARE_INTERFACE(PopupAccessor, "org.okstar.msg.PopupAccessor/0.1");

#endif // POPUPACCESSOR_H
