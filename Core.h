#include "interface.h"
#include <iostream>
#include <string>
#include <gloox/client.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>

using namespace gloox;

class Core : public ConnectionListener, public PresenceHandler, public MessageSessionHandler, public MessageHandler, public RosterListener
{
public:
Core(terminal xterm);
~Core();

output sortie;
input entree;
		
		
// à la connexion
void doSomething();
void onConnect();
void onDisconnect(ConnectionError e);
bool onTLSConnect(const CertInfo& info);
bool connected;


//à la reception de messages
void handleMessageSession(MessageSession* session);
void handleMessage(const Message& msg, MessageSession* session=0);
void handlePresence(const Presence &presence);  	



void handleItemAdded (const JID &jid);
void handleItemSubscribed (const JID &jid);
void handleItemRemoved (const JID &jid);
void handleItemUpdated (const JID &jid);
void handleItemUnsubscribed (const JID &jid);
void handleRoster (const Roster &roster);
void handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
void handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
bool handleSubscriptionRequest (const JID &jid, const std::string &msg);
bool handleUnsubscriptionRequest (const JID &jid, const std::string &msg);
void handleNonrosterPresence (const Presence &presence);
void handleRosterError (const IQ &iq);


};



