#ifndef PSIACCOUNTCONTROLLER_H
#define PSIACCOUNTCONTROLLER_H

#include <QtPlugin>

class PsiAccountControllingHost;

class PsiAccountController {
public:
    virtual ~PsiAccountController() { }

    virtual void setPsiAccountControllingHost(PsiAccountControllingHost *host) = 0;
};

Q_DECLARE_INTERFACE(PsiAccountController, "org.okstar.msg.PsiAccountController/0.1");

#endif // PSIACCOUNTCONTROLLER_H
