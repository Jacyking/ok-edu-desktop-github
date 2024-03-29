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

#ifndef FRIEND_H
#define FRIEND_H

#include "contact.h"
#include "src/core/contactid.h"
#include "src/core/core.h"
#include "src/core/toxid.h"
#include "src/model/status.h"
#include <QObject>
#include <QString>


class Friend : public Contact {
  Q_OBJECT
public:
  Friend(QString friendId,
         const ToxPk &friendPk,
         bool isFriend,
         const QString &userAlias = {},
         const QString &userName = {});

  Friend(const Friend &other) = delete;
  Friend &operator=(const Friend &other) = delete;

  void setName(const QString &name) override;
  void setAlias(const QString &name);
  QString getDisplayedName() const override;
  bool hasAlias() const;
  QString getUserName() const;
  void setStatusMessage(const QString &message);
  QString getStatusMessage() const;

  void setEventFlag(bool f) override;
  bool getEventFlag() const override;

  const ToxPk &getPublicKey() const;
  QString getId() const override;
  const ContactId &getPersistentId() const override;

  void setStatus(Status::Status s);
  Status::Status getStatus() const;

  bool isFriend()const {return  isFriend_;}
signals:
  void nameChanged(const ToxPk &friendId, const QString &name);
  void aliasChanged(const ToxPk &friendId, QString alias);
  void statusChanged(const ToxPk &friendId, Status::Status status);
  void onlineOfflineChanged(const ToxPk &friendId, bool isOnline);
  void statusMessageChanged(const ToxPk &friendId, const QString &message);
  void loadChatHistory();

public slots:

private:
  QString userName;
  QString userAlias;
  QString statusMessage;
  ToxPk friendPk;
  QString friendId;
  bool hasNewEvents;
  Status::Status friendStatus;
  bool isFriend_;
};

#endif // FRIEND_H
