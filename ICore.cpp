/**Copyright 2012 Fabien LUCE
This file is part of Cptalk!.

Cptalk! is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Cptalk! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Cptalk!.  If not, see <http://www.gnu.org/licenses/>.**/




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




