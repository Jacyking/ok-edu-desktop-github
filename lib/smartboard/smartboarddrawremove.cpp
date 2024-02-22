#include "smartboarddrawremove.h"

namespace SmartBoard
{
    DrawRemove::DrawRemove()
    {
    }

    void DrawRemove::setRemoveId(const DrawId &id)
    {
        _id = id;
    }

    const DrawId &DrawRemove::removeId() const
    {
        return _id;
    }
}
