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

#include "groupid.h"
//#include <tox/tox.h>

#include <QByteArray>
#include <QString>

#include <cassert>

/**
 * @class GroupId
 * @brief This class represents a long term persistent group identifier.
 */

/**
 * @brief The default constructor. Creates an empty Tox group ID.
 */
GroupId::GroupId() : ContactId()
{
}

/**
 * @brief The copy constructor.
 * @param other GroupId to copy
 */
GroupId::GroupId(const GroupId& other)
    : ContactId(other.toString().toUtf8())
{
}

GroupId::GroupId(const QByteArray &rawId)
    : ContactId(rawId)
{

}
/**
 * @brief Constructs a GroupId from bytes.
 * @param rawId The bytes to construct the GroupId from. The lenght must be exactly
 *              TOX_CONFERENCE_UID_SIZE, else the GroupId will be empty.
 */
GroupId::GroupId(const lib::messenger::FriendId& rawId)
  : ContactId(rawId)
{

}

/**
 * @brief Get size of public id in bytes.
 * @return Size of public id in bytes.
 */
int GroupId::getSize() const
{
    return username.size();
}

bool GroupId::operator==(const GroupId& other) const
{
    return username == other.username;
}

bool GroupId::operator<(const GroupId& other) const
{
    return username < other.username;
}

