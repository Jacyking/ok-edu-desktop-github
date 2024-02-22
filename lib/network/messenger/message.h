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

#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QRegularExpression>
#include <QString>

#include <vector>

class Friend;

#define tox_max_message_length 1024

#define TOX_CONFERENCE_UID_SIZE 32
#define TOX_ADDRESS_SIZE 10
#define TOX_PUBLIC_KEY_SIZE 10
#define TOX_SECRET_KEY_SIZE 10

enum TOXAV_FRIEND_CALL_STATE {

  /**
   * The empty bit mask. None of the bits specified below are set.
   */
  TOXAV_FRIEND_CALL_STATE_NONE = 0,

  /**
   * Set by the AV core if an error occurred on the remote end or if friend
   * timed out. This is the final state after which no more state
   * transitions can occur for the call. This call state will never be triggered
   * in combination with other call states.
   */
  TOXAV_FRIEND_CALL_STATE_ERROR = 1,

  /**
   * The call has finished. This is the final state after which no more state
   * transitions can occur for the call. This call state will never be
   * triggered in combination with other call states.
   */
  TOXAV_FRIEND_CALL_STATE_FINISHED = 2,

  /**
   * The flag that marks that friend is sending audio.
   */
  TOXAV_FRIEND_CALL_STATE_SENDING_A = 4,

  /**
   * The flag that marks that friend is sending video.
   */
  TOXAV_FRIEND_CALL_STATE_SENDING_V = 8,

  /**
   * The flag that marks that friend is receiving audio.
   */
  TOXAV_FRIEND_CALL_STATE_ACCEPTING_A = 16,

  /**
   * The flag that marks that friend is receiving video.
   */
  TOXAV_FRIEND_CALL_STATE_ACCEPTING_V = 32,

};

typedef enum TOX_ERR_CONFERENCE_SEND_MESSAGE {

  /**
   * The function returned successfully.
   */
  TOX_ERR_CONFERENCE_SEND_MESSAGE_OK,

  /**
   * The conference number passed did not designate a valid conference.
   */
  TOX_ERR_CONFERENCE_SEND_MESSAGE_CONFERENCE_NOT_FOUND,

  /**
   * The message is too long.
   */
  TOX_ERR_CONFERENCE_SEND_MESSAGE_TOO_LONG,

  /**
   * The client is not connected to the conference.
   */
  TOX_ERR_CONFERENCE_SEND_MESSAGE_NO_CONNECTION,

  /**
   * The message packet failed to send.
   */
  TOX_ERR_CONFERENCE_SEND_MESSAGE_FAIL_SEND,

} TOX_ERR_CONFERENCE_SEND_MESSAGE;
typedef TOX_ERR_CONFERENCE_SEND_MESSAGE Tox_Err_Conference_Send_Message;

typedef enum TOX_ERR_FRIEND_SEND_MESSAGE {

  /**
   * The function returned successfully.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_OK,

  /**
   * One of the arguments to the function was NULL when it was not expected.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_NULL,

  /**
   * The friend number did not designate a valid friend.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_FRIEND_NOT_FOUND,

  /**
   * This client is currently not connected to the friend.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_FRIEND_NOT_CONNECTED,

  /**
   * An allocation error occurred while increasing the send queue size.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_SENDQ,

  /**
   * Message length exceeded TOX_MAX_MESSAGE_LENGTH.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_TOO_LONG,

  /**
   * Attempted to send a zero-length message.
   */
  TOX_ERR_FRIEND_SEND_MESSAGE_EMPTY,

} TOX_ERR_FRIEND_SEND_MESSAGE;

typedef TOX_ERR_FRIEND_SEND_MESSAGE Tox_Err_Friend_Send_Message;

typedef enum TOX_ERR_CONFERENCE_TITLE {

  /**
   * The function returned successfully.
   */
  TOX_ERR_CONFERENCE_TITLE_OK,

  /**
   * The conference number passed did not designate a valid conference.
   */
  TOX_ERR_CONFERENCE_TITLE_CONFERENCE_NOT_FOUND,

  /**
   * The title is too long or empty.
   */
  TOX_ERR_CONFERENCE_TITLE_INVALID_LENGTH,

  /**
   * The title packet failed to send.
   */
  TOX_ERR_CONFERENCE_TITLE_FAIL_SEND,

} TOX_ERR_CONFERENCE_TITLE;
typedef TOX_ERR_CONFERENCE_TITLE Tox_Err_Conference_Title;

typedef enum TOX_USER_STATUS {

  /**
   * User is online and available.
   */
  TOX_USER_STATUS_NONE,

  /**
   * User is away. Clients can set this e.g. after a user defined
   * inactivity time.
   */
  TOX_USER_STATUS_AWAY,

  /**
   * User is busy. Signals to other clients that this client does not
   * currently wish to communicate.
   */
  TOX_USER_STATUS_BUSY,

} TOX_USER_STATUS;

typedef TOX_USER_STATUS Tox_User_Status;

typedef enum TOX_ERR_CONFERENCE_JOIN {

  /**
   * The function returned successfully.
   */
  TOX_ERR_CONFERENCE_JOIN_OK,

  /**
   * The cookie passed has an invalid length.
   */
  TOX_ERR_CONFERENCE_JOIN_INVALID_LENGTH,

  /**
   * The conference is not the expected type. This indicates an invalid cookie.
   */
  TOX_ERR_CONFERENCE_JOIN_WRONG_TYPE,

  /**
   * The friend number passed does not designate a valid friend.
   */
  TOX_ERR_CONFERENCE_JOIN_FRIEND_NOT_FOUND,

  /**
   * Client is already in this conference.
   */
  TOX_ERR_CONFERENCE_JOIN_DUPLICATE,

  /**
   * Conference instance failed to initialize.
   */
  TOX_ERR_CONFERENCE_JOIN_INIT_FAIL,

  /**
   * The join packet failed to send.
   */
  TOX_ERR_CONFERENCE_JOIN_FAIL_SEND,

} TOX_ERR_CONFERENCE_JOIN;

typedef TOX_ERR_CONFERENCE_JOIN Tox_Err_Conference_Join;

/**
 * Represents message types for tox_friend_send_message and conference
 * messages.
 *
 * @deprecated All UPPER_CASE enum type names are deprecated. Use the
 *   Camel_Snake_Case versions, instead.
 */
typedef enum TOX_MESSAGE_TYPE {

  /**
   * Normal text message. Similar to PRIVMSG on IRC.
   */
  TOX_MESSAGE_TYPE_NORMAL,

  /**
   * A message describing an user action. This is similar to /me (CTCP ACTION)
   * on IRC.
   */
  TOX_MESSAGE_TYPE_ACTION,

} TOX_MESSAGE_TYPE;

typedef TOX_MESSAGE_TYPE Tox_Message_Type;

typedef enum TOX_FILE_CONTROL {

  /**
   * Sent by the receiving side to accept a file send request. Also sent after a
   * TOX_FILE_CONTROL_PAUSE command to continue sending or receiving.
   */
  TOX_FILE_CONTROL_RESUME,

  /**
   * Sent by clients to pause the file transfer. The initial state of a file
   * transfer is always paused on the receiving side and running on the sending
   * side. If both the sending and receiving side pause the transfer, then both
   * need to send TOX_FILE_CONTROL_RESUME for the transfer to resume.
   */
  TOX_FILE_CONTROL_PAUSE,

  /**
   * Sent by the receiving side to reject a file send request before any other
   * commands are sent. Also sent by either side to terminate a file transfer.
   */
  TOX_FILE_CONTROL_CANCEL,

} TOX_FILE_CONTROL;

typedef TOX_FILE_CONTROL Tox_File_Control;

/**
 * Protocols that can be used to connect to the network or friends.
 *
 * @deprecated All UPPER_CASE enum type names are deprecated. Use the
 *   Camel_Snake_Case versions, instead.
 */
typedef enum TOX_CONNECTION {

  /**
   * There is no connection. This instance, or the friend the state change is
   * about, is now offline.
   */
  TOX_CONNECTION_NONE,

  /**
   * A TCP connection has been established. For the own instance, this means it
   * is connected through a TCP relay, only. For a friend, this means that the
   * connection to that particular friend goes through a TCP relay.
   */
  TOX_CONNECTION_TCP,

  /**
   * A UDP connection has been established. For the own instance, this means it
   * is able to send UDP packets to DHT nodes, but may still be connected to
   * a TCP relay. For a friend, this means that the connection to that
   * particular friend was built using direct UDP packets.
   */
  TOX_CONNECTION_UDP,

} TOX_CONNECTION;
typedef TOX_CONNECTION Tox_Connection;

/**
 * Conference types for the conference_invite event.
 *
 * @deprecated All UPPER_CASE enum type names are deprecated. Use the
 *   Camel_Snake_Case versions, instead.
 */
typedef enum TOX_CONFERENCE_TYPE {

  /**
   * Text-only conferences that must be accepted with the tox_conference_join
   * function.
   */
  TOX_CONFERENCE_TYPE_TEXT,

  /**
   * Video conference. The function to accept these is in toxav.
   */
  TOX_CONFERENCE_TYPE_AV,

} TOX_CONFERENCE_TYPE;
typedef TOX_CONFERENCE_TYPE Tox_Conference_Type;

/**
 * Error codes for peer info queries.
 */
typedef enum TOX_ERR_CONFERENCE_PEER_QUERY {

  /**
   * The function returned successfully.
   */
  TOX_ERR_CONFERENCE_PEER_QUERY_OK,

  /**
   * The conference number passed did not designate a valid conference.
   */
  TOX_ERR_CONFERENCE_PEER_QUERY_CONFERENCE_NOT_FOUND,

  /**
   * The peer number passed did not designate a valid peer.
   */
  TOX_ERR_CONFERENCE_PEER_QUERY_PEER_NOT_FOUND,

  /**
   * The client is not connected to the conference.
   */
  TOX_ERR_CONFERENCE_PEER_QUERY_NO_CONNECTION,

} TOX_ERR_CONFERENCE_PEER_QUERY;

typedef TOX_ERR_CONFERENCE_PEER_QUERY Tox_Err_Conference_Peer_Query;

typedef enum TOX_ERR_BOOTSTRAP {

  /**
   * The function returned successfully.
   */
  TOX_ERR_BOOTSTRAP_OK,

  /**
   * One of the arguments to the function was NULL when it was not expected.
   */
  TOX_ERR_BOOTSTRAP_NULL,

  /**
   * The hostname could not be resolved to an IP address, or the IP address
   * passed was invalid.
   */
  TOX_ERR_BOOTSTRAP_BAD_HOST,

  /**
   * The port passed was invalid. The valid port range is (1, 65535).
   */
  TOX_ERR_BOOTSTRAP_BAD_PORT,

} TOX_ERR_BOOTSTRAP;

typedef TOX_ERR_BOOTSTRAP Tox_Err_Bootstrap;

// NOTE: This could be extended in the future to handle all text processing (see
// ChatMessage::createChatMessage)
enum class MessageMetadataType {
  selfMention,
};

// May need to be extended in the future to have a more varianty type (imagine
// if we wanted to add message replies and shoved a reply id in here)
struct MessageMetadata {
  MessageMetadataType type;
  // Indicates start position within a Message::content
  size_t start;
  // Indicates end position within a Message::content
  size_t end;
};

namespace lib {
namespace IM {

struct Message {
  bool isAction;
  unsigned long id;
  QString sender;
  QString content;
  QDateTime timestamp;
  std::vector<MessageMetadata> metadata;
};

class MessageProcessor {

public:
  /**
   * Parameters needed by all message processors. Used to reduce duplication
   * of expensive data looked at by all message processors
   */
  class SharedParams {

  public:
    QRegularExpression GetNameMention() const { return nameMention; }
    QRegularExpression GetSanitizedNameMention() const {
      return sanitizedNameMention;
    }
    QRegularExpression GetPublicKeyMention() const { return pubKeyMention; }
    void onUserNameSet(const QString &username);
    void setPublicKey(const QString &pk);

  private:
    QRegularExpression nameMention;
    QRegularExpression sanitizedNameMention;
    QRegularExpression pubKeyMention;
  };

  MessageProcessor(const SharedParams &sharedParams);

  std::vector<Message> processOutgoingMessage(bool isAction,
                                              QString const &content);

  Message processIncomingMessage(bool isAction, Message const &message);

  /**
   * @brief Enables mention detection in the processor
   */
  inline void enableMentions() { detectingMentions = true; }

  /**
   * @brief Disables mention detection in the processor
   */
  inline void disableMentions() { detectingMentions = false; };

private:
  bool detectingMentions = false;
  const SharedParams &sharedParams;
};
} // namespace IM
} // namespace lib

#endif /*MESSAGE_H*/
