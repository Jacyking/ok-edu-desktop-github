#ifndef SOUNDACCESSOR_H
#define SOUNDACCESSOR_H

#include <QtPlugin>

class SoundAccessingHost;

class SoundAccessor {
public:
    virtual ~SoundAccessor() { }

    virtual void setSoundAccessingHost(SoundAccessingHost *host) = 0;
};

Q_DECLARE_INTERFACE(SoundAccessor, "org.okstar.msg.SoundAccessor/0.1");

#endif // SOUNDACCESSOR_H
