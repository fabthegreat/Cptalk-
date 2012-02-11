#include "ICore.h"

ICore_XMPP::ICore_XMPP(){

}

ICore_XMPP::~ICore_XMPP(){}



void ICore_XMPP::onDisconnect(ConnectionError e)
		 {
		}

void ICore_XMPP::handlePresence (const Presence &presence){


}



void ICore_XMPP::handleItemAdded (const JID &jid){}
void ICore_XMPP::handleItemSubscribed (const JID &jid){}
void ICore_XMPP::handleItemRemoved (const JID &jid){}
void ICore_XMPP::handleItemUpdated (const JID &jid){}
void ICore_XMPP::handleItemUnsubscribed (const JID &jid){}
void ICore_XMPP::handleRoster (const Roster &roster){

}
void ICore_XMPP::handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){

}

void ICore_XMPP::handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){}
bool ICore_XMPP::handleSubscriptionRequest (const JID &jid, const std::string &msg){return true;}
bool ICore_XMPP::handleUnsubscriptionRequest (const JID &jid, const std::string &msg){return true;}
void ICore_XMPP::handleNonrosterPresence (const Presence &presence){}
void ICore_XMPP::handleRosterError (const IQ &iq){}




