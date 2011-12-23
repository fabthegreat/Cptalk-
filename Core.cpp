#include "Core.h"

Core::Core(terminal& xterm, string j, string passwd)
:jid(j),client(jid,passwd),sortie(xterm.hauteur,xterm.largeur),entree(xterm.hauteur,xterm.largeur){

		/** Chargement des module du client **/
		client.registerConnectionListener( this );
		client.registerMessageSessionHandler( this, 0 );
		client.registerPresenceHandler( this );
		client.rosterManager()->registerRosterListener(this);
		


}

Core::~Core(){}

void Core::doSomething()
{

}


void Core::annonce(string s){
				sortie.annoncer(s);
				entree.refresh();
				update_panels();
}


void Core::onConnect()
		 {
			annonce("Connexion normale reussie");				 

			



			connected=true;
		}

void Core::onDisconnect(ConnectionError e)
		 {
		}

bool Core::onTLSConnect(const CertInfo& info)
		 {
			annonce("Connexion TLS reussie");				 
			return 1;
		}


void Core::handleMessageSession(MessageSession* session)
{
			annonce("Ouverture d'une session de discussion!");				 
}



void Core::handleMessage(const Message& msg, MessageSession* session)
{
}

void Core::handlePresence (const Presence &presence){


}



void Core::handleItemAdded (const JID &jid){}
void Core::handleItemSubscribed (const JID &jid){}
void Core::handleItemRemoved (const JID &jid){}
void Core::handleItemUpdated (const JID &jid){}
void Core::handleItemUnsubscribed (const JID &jid){}
void Core::handleRoster (const Roster &roster){
		//std::cout << "un contact vient de changer de statut!";

}
void Core::handleRosterPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){

				string s="Nouveau status de "+ item.jid()+": "+msg;
				annonce(s);				 
				connected=true;
}

void Core::handleSelfPresence (const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){}
bool Core::handleSubscriptionRequest (const JID &jid, const std::string &msg){return true;}
bool Core::handleUnsubscriptionRequest (const JID &jid, const std::string &msg){return true;}
void Core::handleNonrosterPresence (const Presence &presence){}
void Core::handleRosterError (const IQ &iq){}
