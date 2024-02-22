/*
    Copyright © 2019 by The qTox Project Contributors

    This file is part of qTox, a Qt-based graphical interface for Tox.

    qTox is libre software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    qTox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with qTox.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "toxpk.h"

//#include <tox/tox.h>

#include <QByteArray>
#include <QString>

#include <cassert>

/**
 * @class ToxPk
 * @brief This class represents a Tox Public Key, which is a part of Ok ID.
 */

/**
 * @brief The default constructor. Creates an empty Tox key.
 */
ToxPk::ToxPk() : ContactId()
{
}

/**
 * @brief The copy constructor.
 * @param other ToxPk to copy
 */
ToxPk::ToxPk(const ToxPk& other)
    : ContactId(other.toString().toUtf8())
{
}

/**
 * @brief Constructs a ToxPk from bytes.
 * @param rawId The bytes to construct the ToxPk from. The lenght must be exactly
 *              TOX_PUBLIC_KEY_SIZE, else the ToxPk will be empty.
 */
ToxPk::ToxPk(const QByteArray& rawId)
    : ContactId(rawId)
{
}

/**
 * @brief Constructs a ToxPk from bytes.
 * @param rawId The bytes to construct the ToxPk from, will read exactly
 * TOX_PUBLIC_KEY_SIZE from the specified buffer.
 */
ToxPk::ToxPk(const lib::messenger::FriendId& rawId)
    : ContactId( rawId )
{
}

bool ToxPk::operator==(const ToxPk &other) const {
    return other.username.toLower() == username.toLower() ;//&& other.server == server;
}

bool ToxPk::operator<(const ToxPk &other) const {
  return username < other.username ;// && server < other.server;
}

/**
 * @brief Get size of public key in bytes.
 * @return Size of public key in bytes.
 */
int ToxPk::getSize() const
{
    return toString().size();
}
