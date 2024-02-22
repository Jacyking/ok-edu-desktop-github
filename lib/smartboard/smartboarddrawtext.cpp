#include "smartboarddrawtext.h"

namespace SmartBoard {

DrawText::DrawText() : DrawItem ()
{

}

DrawText::~DrawText()
{
}

DrawText::DrawText(const std::string& id, const std::string& text){
    _id=id;
    _text = id;
}

const std::string& DrawText::text( ) const{
    return _text;
}

}
