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

#include "friendmessagedispatcher.h"
#include "src/model/status.h"
#include "src/persistence/settings.h"

namespace {

/**
 * @brief Sends message to friend using messageSender
 * @param[in] messageSender
 * @param[in] f
 * @param[in] message
 * @param[out] receipt
 */
bool sendMessageToCore(ICoreFriendMessageSender &messageSender, const Friend &f,
                       const Message &message, ReceiptNum &receipt,
                       bool encrypt) {
  QString friendId = f.getId();

  auto sendFn = message.isAction
                    ? std::mem_fn(&ICoreFriendMessageSender::sendAction)
                    : std::mem_fn(&ICoreFriendMessageSender::sendMessage);

  return sendFn(messageSender, friendId, message.content, receipt, encrypt);
}
} // namespace

FriendMessageDispatcher::FriendMessageDispatcher(
    Friend &f_, MessageProcessor processor_,
    ICoreFriendMessageSender &messageSender_)
    : f(f_), messageSender(messageSender_),
      offlineMsgEngine(&f_, &messageSender_), processor(std::move(processor_)) {
  connect(&f, &Friend::onlineOfflineChanged, this,
          &FriendMessageDispatcher::onFriendOnlineOfflineChanged);
}

/**
 * @see IMessageSender::sendMessage
 */
std::pair<DispatchedMessageId, DispatchedMessageId>
FriendMessageDispatcher::sendMessage(bool isAction, const QString &content, bool encrypt) {
  qDebug() << "FriendMessageDispatcher::sendMessage" << content;

  const auto firstId = nextMessageId;
  auto lastId = nextMessageId;

  for (const auto &message : processor.processOutgoingMessage(isAction, content)) {

    auto messageId = nextMessageId++;
    lastId = messageId;
    auto onOfflineMsgComplete = [this, messageId] {
      qDebug() << "FriendMessageDispatcher::onOfflineMsgComplete messageId:" << messageId.get();
      emit this->messageComplete(messageId);
    };

    ReceiptNum receipt;

    bool messageSent = false;

    emit this->messageSent(messageId, message);

//    if (Status::isOnline(f.getStatus())) {
      messageSent = sendMessageToCore(messageSender, f, message, receipt, encrypt);
//    }

    if (!messageSent) {
      offlineMsgEngine.addUnsentMessage(message, onOfflineMsgComplete);
    } else {
      offlineMsgEngine.addSentMessage(receipt, message, onOfflineMsgComplete);
    }

  }
  return std::make_pair(firstId, lastId);
}

/**
 * @brief Handles received message from toxcore
 * @param[in] isAction True if action message
 * @param[in] content Unprocessed toxcore message
 */
void FriendMessageDispatcher::onMessageReceived(bool isAction,
                                                const lib::messenger::IMMessage& msg) {
  emit this->messageReceived(f.getPublicKey(), processor.processIncomingMessage(isAction, msg.body, msg.from, msg.time));
}


/**
 * @brief Handles received receipt from toxcore
 * @param[in] receipt receipt id
 */
void FriendMessageDispatcher::onReceiptReceived(ReceiptNum receipt) {
  offlineMsgEngine.onReceiptReceived(receipt);
}

/**
 * @brief Handles status change for friend
 * @note Parameters just to fit slot api
 */
void FriendMessageDispatcher::onFriendOnlineOfflineChanged(const ToxPk &,
                                                           bool isOnline) {
  if (isOnline) {
    offlineMsgEngine.deliverOfflineMsgs();
  }
}

/**
 * @brief Clears all currently outgoing messages
 */
void FriendMessageDispatcher::clearOutgoingMessages() {
  offlineMsgEngine.removeAllMessages();
}
