#ifndef IM_CONFERENCE_H
#define IM_CONFERENCE_H

#include "base/timer.h"
#include "gloox/client.h"
#include "gloox/conference.h"
#include "gloox/jinglesessionhandler.h"
#include "gloox/mucroom.h"
#include <memory>

namespace lib {
namespace messenger {

using namespace gloox;

class IMConference : public QObject,
                     public ConferenceHandler,
                     public DiscoHandler {
  Q_OBJECT
public:
  IMConference(Client *client, Jingle::SessionHandler *sessionHandler);

  void start(const JID &jid);

  void join(const std::string &room);

  void setVideoMute(const std::string &room);

  // Disco handler
  virtual void handleDiscoInfo(const JID &from,     //
                               const Disco::Info &, //
                               int ontext) override;

  virtual void handleDiscoItems(const JID &from,      //
                                const Disco::Items &, //
                                int context) override;

  virtual void handleDiscoError(const JID &from,      //
                                const gloox::Error *, //
                                int context) override;

  virtual void onStart(const gloox::Conference *j) override;

private:
  Client *_client;
  Jingle::SessionHandler *_sessionHandler;

  std::unique_ptr<gloox::ConferenceManager> _conferenceManager;
  std::shared_ptr<::base::DelayedCallTimer> delayCaller_;

signals:
  void groupListReceived(const QString &peerId);

};
} // namespace IM
} // namespace lib

#endif
