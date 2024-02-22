#ifndef SMARTBOARDDRAWTEXT_H
#define SMARTBOARDDRAWTEXT_H

#include "smartboard.h"

namespace SmartBoard
{

    class DrawText : public DrawItem
    {
    private:
        std::string _text;

    public:
        DrawText();
        ~DrawText();
        
        DrawText(const std::string &id, const std::string &text);

        const std::string &text() const;
    };

}
#endif // SMARTBOARDDRAWTEXT_H
