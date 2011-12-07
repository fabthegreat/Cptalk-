#include "Core.h"

void Core::doSomething()
{

}

void Core::onConnect()
		 {
				 std::cout << "connecté en mode normal!" << std::endl ;			//             // presence info
				 connected=true;
		}

void Core::onDisconnect(ConnectionError e)
		 {
				 std::cout << "deconnecté!" << std::endl;			//             // presence info
				//             // presence info
		}

bool Core::onTLSConnect(const CertInfo& info)
		 {
				std::cout << "connecté en TLS!" << std::endl;			//             // presence info
				//             // presence info
				return 1;
		}


void Core::handleMessageSession(MessageSession* session)
{
	session->registerMessageHandler(this);
	session->send( "Message de session!", "No Subject" );
}



void Core::handleMessage(const Message& msg, MessageSession* session)
{
	std::cout << "un message a été envoyé automatiquement" << std::endl;
	session->send( "Message de message!", "No Subject" );
}

void Core::handlePresence (const Presence &presence){


}



void Core::handleItemAdded (const JID &jid){}
void Core::handleItemSubscribed (const JID &jid){}
void Core::handleItemRemoved (const JID &jid){}
void Core::handleItemUpdated (const JID &jid){}
void Core::handleItemUnsubscribed (const JID &jid){}
void Core::handleRoster (const Roster &roster){
		std::cout << "un contact vient de changer de statut!";

}
void Core::handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){

		std::cout << "un contact vient de changer de statut!";
}

void Core::handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){}
bool Core::handleSubscriptionRequest (const JID &jid, const std::string &msg){return true;}
bool Core::handleUnsubscriptionRequest (const JID &jid, const std::string &msg){return true;}
void Core::handleNonrosterPresence (const Presence &presence){}
void Core::handleRosterError (const IQ &iq){}
