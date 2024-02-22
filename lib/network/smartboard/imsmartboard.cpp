#include "imsmartboard.h"
#include <gloox/gloox.h>
#include <gloox/pubsubevent.h>
#include <gloox/pubsubitem.h>

#include "lib/smartboard/smartboarddraw.h"
#include "lib/smartboard/smartboarddrawline.h"

#include "lib/smartboard/smartboardcontroller.h"
#include "lib/smartboard/smartboardcontrollervoice.h"

#include <base/logs.h>

#include "../session/AuthSession.h"

namespace network
{
    namespace smartboard
    {

#define PUBSUB_SERVICE gloox::JID("pubsub.rtc.chuanshaninfo.com")
        const std::string PUBSUB_NODE = "SmartBoard";

        IMSmartBoard::IMSmartBoard() : _jingle(nullptr),
                                       _painterDispatcher(nullptr)
        {
            DEBUG_LOG(("begin"));

            DEBUG_LOG(("end"));
        }

        IMSmartBoard::~IMSmartBoard()
        {
            DEBUG_LOG(("..."));
        }

        void IMSmartBoard::setJingle(jingle::IMJingle *jingle)
        {
            if (!jingle)
            {
                DEBUG_LOG(("jingle is nullptr"));
                return;
            }

            _jingle = jingle;
            _jingle->registerHandler(this);
            const session::AuthSession *session = _jingle->session();
            if (!session)
            {
                DEBUG_LOG(("session is nullptr"));
                return;
            }
            _pubsubManager = std::make_shared<gloox::PubSub::Manager>(session->client());
        }

        void IMSmartBoard::jingleInitiate()
        {
            DEBUG_LOG(("..."));
        }

        void IMSmartBoard::jingleAccept()
        {
            DEBUG_LOG(("..."));

            // _pubsubManager->subscribe(PUBSUB_SERVICE, PUBSUB_NODE, this, gloox::JID(), gloox::PubSub::SubscriptionNodes, 0);
        }

        void IMSmartBoard::jingleTerminate()
        {
            DEBUG_LOG(("..."));
        }

        void IMSmartBoard::handleItem(const gloox::JID &service,
                                      const std::string &node,
                                      const gloox::Tag *entry)
        {
            DEBUG_LOG(("begin args service:%1 node:%2")
                          .arg(qstring(service.full()))
                          .arg(qstring(node)));
        }

        void IMSmartBoard::handleItems(const std::string &id,
                                       const gloox::JID &service,
                                       const std::string &node,
                                       const gloox::PubSub::ItemList &itemList,
                                       const gloox::Error *error)
        {
            // DEBUG_LOG(("begin args id:%1 service:%2 node:%3 itemList:%4")
            //               .arg(qstring(id))
            //               .arg(qstring(service.full()))
            //               .arg(qstring(node))
            //               .arg((itemList.size())));

            // if (error != nullptr)
            // {
            //     DEBUG_LOG(("error:%1").arg(qstring(error->text())));
            //     return;
            // }

            //    for(auto item: itemList){
            //        if(item->payload() != nullptr){
            //            DEBUG_LOG(("%1").arg(qstring(item->payload()->name())));
            //        }
            //    }
        }

        void IMSmartBoard::handleItemPublication(const std::string &id,
                                                 const gloox::JID &service,
                                                 const std::string &node,
                                                 const gloox::PubSub::ItemList &itemList,
                                                 const gloox::Error *error)
        {
            // DEBUG_LOG(("begin args id:%1 service:%2 node:%3 itemList:%4")
            //               .arg(qstring(id))
            //               .arg(qstring(service.full()))
            //               .arg(qstring(node))
            //               .arg(itemList.size()));

            // if (error != nullptr)
            // {
            //     DEBUG_LOG(("error:%1").arg(qstring(error->text())));
            //     return;
            // }

            //    for(auto item: itemList){
            //        DEBUG_LOG(("item.id:%1").arg(qstring(item->id())));
            //        _pubsubManager->requestItems(service, node, item->id(), 100, this);
            //    }
        }

        void IMSmartBoard::handleItemDeletion(const std::string &id,
                                              const gloox::JID &service,
                                              const std::string &node,
                                              const gloox::PubSub::ItemList &itemList,
                                              const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleSubscriptionResult(const std::string &id,
                                                    const gloox::JID &service,
                                                    const std::string &node,
                                                    const std::string &sid,
                                                    const gloox::JID &jid,
                                                    const gloox::PubSub::SubscriptionType subType,
                                                    const gloox::Error *error)
        {
            // DEBUG_LOG(("begin args id:%1 service:%2 node:%3")
            //               .arg(qstring(id))
            //               .arg(qstring(service.full()))
            //               .arg(qstring(node)));

            // if (error != nullptr)
            // {
            //     DEBUG_LOG(("error:%1").arg(qstring(error->text())));
            //     return;
            // }

            // DEBUG_LOG(("jid:%1 SubscriptionType:%2 sid:3")
            //               .arg(qstring(jid.full()))
            //               .arg(subType)
            //               .arg(qstring(sid)));

            // switch (subType)
            // {
            // case gloox::PubSub::SubscriptionNone:
            //     break;
            // case gloox::PubSub::SubscriptionSubscribed:
            //     break;
            // case gloox::PubSub::SubscriptionPending:
            //     break;
            // case gloox::PubSub::SubscriptionUnconfigured:
            //     break;
            // case gloox::PubSub::SubscriptionInvalid:
            //     break;
            // }
        }

        void IMSmartBoard::handleUnsubscriptionResult(const std::string &id,
                                                      const gloox::JID &service,
                                                      const gloox::Error *error)
        {
            // DEBUG_LOG(("begin args id:%1 service:%2 error:%3")
            //               .arg(qstring(id))
            //               .arg(qstring(service.full()))
            //               .arg(qstring(error->text())));
        }

        void IMSmartBoard::handleSubscriptionOptions(const std::string &id,
                                                     const gloox::JID &service, const gloox::JID &jid, const std::string &node, const gloox::DataForm *options, const std::string &sid, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleSubscriptionOptionsResult(const std::string &id,
                                                           const gloox::JID &service, const gloox::JID &jid, const std::string &node, const std::string &sid, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleSubscribers(const std::string &id,
                                             const gloox::JID &service, const std::string &node, const gloox::PubSub::SubscriptionList &list, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleSubscribersResult(const std::string &id,
                                                   const gloox::JID &service, const std::string &node, const gloox::PubSub::SubscriberList *list, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleAffiliates(const std::string &id,
                                            const gloox::JID &service, const std::string &node, const gloox::PubSub::AffiliateList *list, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleAffiliatesResult(const std::string &id,
                                                  const gloox::JID &service,
                                                  const std::string &node,
                                                  const gloox::PubSub::AffiliateList *list,
                                                  const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleNodeConfig(const std::string &id,
                                            const gloox::JID &service,
                                            const std::string &node,
                                            const gloox::DataForm *config,
                                            const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleNodeConfigResult(const std::string &id,
                                                  const gloox::JID &service,
                                                  const std::string &node,
                                                  const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleNodeCreation(const std::string &id,
                                              const gloox::JID &service,
                                              const std::string &node,
                                              const gloox::Error *error)
        {
            // DEBUG_LOG(("begin args id:%1 service:%2 node:%3 error:%4")
            //               .arg(qstring(id))
            //               .arg(qstring(service.full()))
            //               .arg(qstring(node))
            //               .arg(qstring(error->text())));
            // if (error != nullptr)
            // {
            //     return;
            // }

            DEBUG_LOG(("end"));
        }

        void IMSmartBoard::handleNodeDeletion(const std::string &id, const gloox::JID &service, const std::string &node, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleNodePurge(const std::string &id, const gloox::JID &service, const std::string &node, const gloox::Error *error)
        {
        }

        void IMSmartBoard::handleSubscriptions(const std::string &id,
                                               const gloox::JID &service,
                                               const gloox::PubSub::SubscriptionMap &subMap,
                                               const gloox::Error *error)
        {
            // DEBUG_LOG(("begin args id:%1 service:%2 subMap:%3")
            //               .arg(qstring(id))
            //               .arg(qstring(service.full()))
            //               .arg(subMap.size()));

            // if (error != nullptr)
            // {
            //     DEBUG_LOG(("error:%1").arg(qstring(error->text())));
            //     return;
            // }

            DEBUG_LOG(("end"));
        }

        void IMSmartBoard::handleAffiliations(const std::string &id,
                                              const gloox::JID &service,
                                              const gloox::PubSub::AffiliationMap &affMap,
                                              const gloox::Error *error)
        {
            DEBUG_LOG(("begin args id:%1 service:%2 subMap:%3")
                          .arg(qstring(id))
                          .arg(qstring(service.full()))
                          .arg(affMap.size()));

            // if (error != nullptr)
            // {
            //     DEBUG_LOG(("error:%1").arg(qstring(error->text())));
            //     return;
            // }

            DEBUG_LOG(("end"));
        }

        void IMSmartBoard::handleDefaultNodeConfig(const std::string &id,
                                                   const gloox::JID &service,
                                                   const gloox::DataForm *config,
                                                   const gloox::Error *error)
        {
            DEBUG_LOG(("begin args id:%1 service:%2")
                          .arg(qstring(id))
                          .arg(qstring(service.full())));

            // if (error != nullptr)
            // {
            //     DEBUG_LOG(("error:%1").arg(qstring(error->text())));
            //     return;
            // }

            // DEBUG_LOG(("config title:%1").arg(qstring(config->title())));

            DEBUG_LOG(("end"));
        }

        void IMSmartBoard::sentEvent(const gloox::PubSub::ItemList &items)
        {
            emit pubsubEvent(const_cast<gloox::PubSub::ItemList &>(items));
        }

        void IMSmartBoard::sendDraw(std::shared_ptr<SmartBoard::SmartBoardDraw> draw)
        {
            DEBUG_LOG_S(L_DEBUG) << draw.get();
            if (!draw)
            {
                DEBUG_LOG_S(L_WARN) << "draw is nullptr!";
                return;
            }

            DEBUG_LOG_S(L_WARN) << "The end.";
            return;

            gloox::PubSub::ItemList items;

            gloox::PubSub::Item *item = new gloox::PubSub::Item();
            item->setPayload(draw->tag());
            
            items.push_back(item);

            _pubsubManager->publishItem(PUBSUB_SERVICE, PUBSUB_NODE, items, nullptr, this);
        }

        void IMSmartBoard::receiveDraw(SmartBoard::SmartBoardDraw *draw)
        {
            DEBUG_LOG_S(L_INFO) << draw;
            emit receivedDraw(draw);
        }

        void IMSmartBoard::sendController(std::shared_ptr<SmartBoard::Controller> controller)
        {
            DEBUG_LOG_S(L_DEBUG) << controller.get();
            if (!controller)
            {
                return;
            }

            gloox::PubSub::ItemList items;

            gloox::PubSub::Item *item = new gloox::PubSub::Item();
            item->setPayload(controller->tag());

            items.push_back(item);

            _pubsubManager->publishItem(PUBSUB_SERVICE, PUBSUB_NODE, items, nullptr, this);
        }

        void IMSmartBoard::receiveController(SmartBoard::Controller *controller)
        {
            DEBUG_LOG_S(L_INFO) << controller;
            if (!controller)
                return;

                // TODO
            // const SmartBoard::UserList &userList = controller->userList();
            // const SmartBoard::ControllerVoice *cVoice = controller->findPlugin<SmartBoard::ControllerVoice>(SmartBoard::ControllerType::Voice);
            // if (cVoice)
            // {

                // bool mute = cVoice->action() == SmartBoard::Action::ON;

                //
                // emit ss(userList, mute);
            // }
            //    emit receivedController(controller);
        }

    }
}
