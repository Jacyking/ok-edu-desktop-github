/*
    Copyright © 2014-2019 by The qTox Project Contributors

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

#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <cstdint>

template <class T> class QList;
template <class A, class B> class QHash;
class Friend;
class QByteArray;
class QString;
class ToxPk;

class FriendList {
public:
  static Friend *addFriend(QString friendId, const ToxPk &friendPk, bool isFriend);
  static Friend *findFriend(const ToxPk &friendPk);
  static const ToxPk &id2Key(QString friendId);
  static QList<Friend *> getAllFriends();
  static void removeFriend(const ToxPk &friendPk, bool fake = false);
  static void clear();
  static QString decideNickname(const ToxPk &friendPk, const QString &origName);

private:
  static QHash<ToxPk, Friend *> friendList;
  static QHash<QString, ToxPk> id2key;
};

#endif // FRIENDLIST_H
