#ifndef CORE_H
#define CORE_H


#include <iostream>
#include <string>
#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>


using namespace gloox;


class ICore_XMPP : public ConnectionListener, public PresenceHandler, public MessageSessionHandler, public MessageHandler, public RosterListener
{
public:
ICore_XMPP();
~ICore_XMPP();


// à la connexion
virtual void onConnect()=0;
virtual bool onTLSConnect(const CertInfo& info)=0;
void onDisconnect(ConnectionError e);



//à la reception de messages
virtual void handleMessageSession(MessageSession* session)=0;
virtual void handleMessage(const Message& msg, MessageSession* session=0)=0;

void handlePresence(const Presence &presence);  	



void handleItemAdded (const JID &jid);
void handleItemSubscribed (const JID &jid);
void handleItemRemoved (const JID &jid);
void handleItemUpdated (const JID &jid);
void handleItemUnsubscribed (const JID &jid);
void handleRoster (const Roster &roster);
virtual void handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg)=0;
void handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
bool handleSubscriptionRequest (const JID &jid, const std::string &msg);
bool handleUnsubscriptionRequest (const JID &jid, const std::string &msg);
void handleNonrosterPresence (const Presence &presence);
void handleRosterError (const IQ &iq);


};

#endif
