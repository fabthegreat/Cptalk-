#include "Core.h"

Core_XMPP::Core_XMPP(){

}

Core_XMPP::~Core_XMPP(){}


void Core_XMPP::onConnect()
		 {
		}

void Core_XMPP::onDisconnect(ConnectionError e)
		 {
		}

bool Core_XMPP::onTLSConnect(const CertInfo& info)
		 {

			return true;	

		}





void Core_XMPP::handleMessageSession(MessageSession* session)
{
}



void Core_XMPP::handleMessage(const Message& msg, MessageSession* session)
{
}

void Core_XMPP::handlePresence (const Presence &presence){


}



void Core_XMPP::handleItemAdded (const JID &jid){}
void Core_XMPP::handleItemSubscribed (const JID &jid){}
void Core_XMPP::handleItemRemoved (const JID &jid){}
void Core_XMPP::handleItemUpdated (const JID &jid){}
void Core_XMPP::handleItemUnsubscribed (const JID &jid){}
void Core_XMPP::handleRoster (const Roster &roster){

}
void Core_XMPP::handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){

}

void Core_XMPP::handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){}
bool Core_XMPP::handleSubscriptionRequest (const JID &jid, const std::string &msg){return true;}
bool Core_XMPP::handleUnsubscriptionRequest (const JID &jid, const std::string &msg){return true;}
void Core_XMPP::handleNonrosterPresence (const Presence &presence){}
void Core_XMPP::handleRosterError (const IQ &iq){}
