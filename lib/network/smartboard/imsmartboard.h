#ifndef IMSMARTBOARD_H
#define IMSMARTBOARD_H

#ifdef Q_OS_WIN
    #undef DrawText //避免windows宏冲突
#endif

#include <memory>

#include <QObject>

#include "lib/smartboard/smartboard.h"
#include "lib/smartboard/smartboardcontroller.h"
#include "lib/smartboard/smartboardcontrollervoice.h"
#include "lib/smartboard/smartboarddraw.h"

namespace painter {
    class PainterDispatcher;
}

namespace network{
namespace smartboard {

extern const std::string PUBSUB_NODE;
extern const std::string PUBSUB_SERVICE;

class IMSmartBoard :
        public QObject,
        public gloox::PubSub::ResultHandler,
        public jingle::IMJingleHandler
{
    Q_OBJECT
public:
    IMSmartBoard();
    virtual ~IMSmartBoard() override;

    virtual std::shared_ptr<gloox::PubSub::Manager> getPubSubManager() const{
        return _pubsubManager;
    }


    virtual void setDispatcher(painter::PainterDispatcher* painterDispatcher){
        _painterDispatcher = painterDispatcher;
    }

    //
    virtual void setJingle(network::jingle::IMJingle* jingle);


    //Self
    virtual void sentEvent(const gloox::PubSub::ItemList& items);

    virtual void sendDraw(std::shared_ptr<SmartBoard::SmartBoardDraw> draw);
    virtual void receiveDraw(SmartBoard::SmartBoardDraw* draw);

    virtual void sendController(std::shared_ptr<SmartBoard::Controller> controller);
    virtual void receiveController(SmartBoard::Controller *controller);


protected:
    // IMJingleHandler interface
    virtual void jingleInitiate() override;
    virtual void jingleAccept() override;
    virtual void jingleTerminate() override;

    //SmartBoard
//    virtual void handleSessionAction (SmartBoard::Action action,
//                                      SmartBoard::Session *session,
//                                      const SmartBoard::Session::SmartBoard *smartboard,
//                                      const IQ& iq) override;

//    virtual void handleSessionActionError (SmartBoard::Action action,
//                                           SmartBoard::Session *session,
//                                           const gloox::Error *error) override;

//    virtual void handleIncomingSession (SmartBoard::Session *session) override;


    //PubSub
    virtual void handleItem( const gloox::JID& service,
                                     const std::string& node,
                                     const gloox::Tag* entry ) override;

    virtual void handleItems( const std::string& id,
                                     const gloox::JID& service,
                                     const std::string& node,
                                     const gloox::PubSub::ItemList& itemList,
                                     const gloox::Error* error = nullptr ) override ;

    virtual void handleItemPublication( const std::string& id,
                                                const gloox::JID& service,
                                                const std::string& node,
                                                const gloox::PubSub::ItemList& itemList,
                                                const gloox::Error* error = nullptr ) override;

    virtual void handleItemDeletion( const std::string& id,
                                             const gloox::JID& service,
                                             const std::string& node,
                                             const gloox::PubSub::ItemList& itemList,
                                             const gloox::Error* error = nullptr ) override;

    virtual void handleSubscriptionResult( const std::string& id,
                                                   const gloox::JID& service,
                                                   const std::string& node,
                                                   const std::string& sid,
                                                   const gloox::JID& jid,
                                                   const gloox::PubSub::SubscriptionType subType,
                                                   const gloox::Error* error = nullptr ) override;

    virtual void handleUnsubscriptionResult( const std::string& id,
                                                    const gloox::JID& service,
                                                    const gloox::Error* error = nullptr ) override;

    virtual void handleSubscriptionOptions( const std::string& id,
                                                   const gloox::JID& service,
                                                   const gloox::JID& jid,
                                                   const std::string& node,
                                                   const gloox::DataForm* options,
                                                   const std::string& sid,
                                                   const gloox::Error* error = nullptr ) override;

    virtual void handleSubscriptionOptionsResult( const std::string& id,
                                                         const gloox::JID& service,
                                                         const gloox::JID& jid,
                                                         const std::string& node,
                                                         const std::string& sid,
                                                         const gloox::Error* error = nullptr ) override;

    virtual void handleSubscribers( const std::string& id,
                                            const gloox::JID& service,
                                            const std::string& node,
                                            const gloox::PubSub::SubscriptionList& list,
                                            const gloox::Error* error = nullptr ) override;

    virtual void handleSubscribersResult( const std::string& id,
                                                  const gloox::JID& service,
                                                  const std::string& node,
                                                  const gloox::PubSub::SubscriberList* list,
                                                  const gloox::Error* error = nullptr ) override;

    virtual void handleAffiliates( const std::string& id,
                                           const gloox::JID& service,
                                           const std::string& node,
                                           const gloox::PubSub::AffiliateList* list,
                                           const gloox::Error* error = nullptr ) override;

    virtual void handleAffiliatesResult( const std::string& id,
                                                 const gloox::JID& service,
                                                 const std::string& node,
                                                 const gloox::PubSub::AffiliateList* list,
                                                 const gloox::Error* error = nullptr ) override;

    virtual void handleNodeConfig( const std::string& id,
                                          const gloox::JID& service,
                                          const std::string& node,
                                          const gloox::DataForm* config,
                                          const gloox::Error* error = nullptr ) override;

    virtual void handleNodeConfigResult( const std::string& id,
                                         const gloox::JID& service,
                                         const std::string& node,
                                         const gloox::Error* error = nullptr ) override;

    virtual void handleNodeCreation( const std::string& id,
                                             const gloox::JID& service,
                                             const std::string& node,
                                             const gloox::Error* error = nullptr ) override;

    virtual void handleNodeDeletion( const std::string& id,
                                             const gloox::JID& service,
                                             const std::string& node,
                                             const gloox::Error* error = nullptr ) override;

    virtual void handleNodePurge( const std::string& id,
                                          const gloox::JID& service,
                                          const std::string& node,
                                          const gloox::Error* error = nullptr ) override;

    virtual void handleSubscriptions( const std::string& id,
                                             const gloox::JID& service,
                                             const gloox::PubSub::SubscriptionMap& subMap,
                                             const gloox::Error* error = nullptr) override;

    virtual void handleAffiliations( const std::string& id,
                                             const gloox::JID& service,
                                             const gloox::PubSub::AffiliationMap& affMap,
                                             const gloox::Error* error = nullptr ) override;

    virtual void handleDefaultNodeConfig( const std::string& id,
                                                  const gloox::JID& service,
                                                  const gloox::DataForm* config,
                                                  const gloox::Error* error = nullptr ) override;

private:

    jingle::IMJingle* _jingle;

    std::shared_ptr<gloox::PubSub::Manager> _pubsubManager;

    painter::PainterDispatcher *_painterDispatcher;



signals:
    void receivedDraw(SmartBoard::SmartBoardDraw*);
    void receivedController(SmartBoard::Controller*);



    void pubsubEvent(gloox::PubSub::ItemList& items);

    void ss(const std::list<std::string>&, bool mute);

};


}
}
#endif // IMSMARTBOARD_H
