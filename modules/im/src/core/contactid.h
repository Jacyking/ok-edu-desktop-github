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

#ifndef CONTACTID_H
#define CONTACTID_H

#include <QByteArray>
#include <QString>
#include <cstdint>
#include <QHash>
#include <memory>

#include "lib/messenger/messenger.h"

class ContactId : public lib::messenger::FriendId
{
public:
    virtual ~ContactId() = default;
    ContactId& operator=(const ContactId& other) = default;
    ContactId& operator=(ContactId&& other) = default;
    bool operator==(const ContactId& other) const;
    bool operator!=(const ContactId& other) const;
    bool operator<(const ContactId& other) const;

    QByteArray getByteArray() const;
    bool isEmpty() const;
    virtual int getSize() const = 0;

    QString getUsername() const;
    QString getServer() const;
//    QString getResource() const;

protected:
    ContactId();
    explicit ContactId(const lib::messenger::FriendId& rawId);
    explicit ContactId(const QByteArray &rawId);

};

inline uint qHash(const ContactId& id)
{
    return qHash(id.getByteArray());
}

using ContactIdPtr = std::shared_ptr<const ContactId>;

#endif // CONTACTID_H
