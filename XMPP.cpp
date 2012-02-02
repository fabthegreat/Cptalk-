#include "XMPP.h"
#include "ICore.h"
#include "Linker.h"


////////////////////////////////////////////////
//----------> Core
void Core::register_linker(Linker& linker){
	ptr_linker=&linker;
}

void Core::write_string(string s){
	Line line(s);
	send_line(line);
	launch_output_refresh();
}

void Core::send_line(Line line){
	ptr_linker->command_router(line);

}

void Core::launch_output_reset(){
	ptr_linker->output_reset();
}

void Core::launch_output_refresh(){
	ptr_linker->output_refresh();
}

void Core::onConnect(){
	connected=true;
	write_string("Connected to the XMPP server!");
}

bool Core::onTLSConnect(const CertInfo& info){
	write_string("Connected in TLS to the XMPP server!");
	return true;	
}

void Core::handleRosterPresence(const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg){
	write_string("You have received a status update of: "+ item.jid() + " (" + msg + ")");
	update_roster_choice();
}		

void Core::handleMessage(const Message& msg, MessageSession* session){
	write_string(session->target().full() + ", " + session->target().bare() + " -> " + msg.body());
	// to debug
	//print_session_id(session->target().bare());
}

void Core::handleMessageSession(MessageSession* session){
	ptr_cpclient->register_session(session);
	session->registerMessageHandler(this);
	ptr_cpclient->add_session(session);
}


void Core::register_cpclient(CpClient* cpclient){
	ptr_cpclient=cpclient;
}


void Core::launch_connect(){
	if (connected==false){
		ptr_cpclient->launch_connect();}
	else {
		write_string("You\'re already connected!");
	}
}

void Core::launch_disconnect(){
	if (connected==true){
		ptr_cpclient->launch_disconnect();}
	else {
		write_string("You\'re already disconnected!");
	}
}

void Core::list_roster(){
		Roster* roster;
		roster=ptr_cpclient->get_roster();
		Roster::iterator it;


		for ( it=(*roster).begin() ; it != (*roster).end(); it++ ){
				if ((*it).second->online()){
					write_string("(o): "+(*it).first);
				} else {
					write_string("(x): "+(*it).first);
				}
		}
}

void Core::update_roster_choice(){
		vector<string> list_roster;
		Roster* roster;
		roster=ptr_cpclient->get_roster();
		Roster::iterator it;


		for ( it=(*roster).begin() ; it != (*roster).end(); it++ ){
				if ((*it).second->online()){
						list_roster.push_back((*it).first);
				} 
		}
		ptr_linker->update_roster_choice(list_roster);	

}

// to debug
void Core::print_session_id(const string bare){
	write_string(ptr_cpclient->get_session_from_bare(bare)->threadID());	
}


MessageSession* Core::get_session_from_bare(const string bare){
	
	// warning: manage session list in core and not in cpclient!!
	return ptr_cpclient->get_session_from_bare(bare);
}


JID Core::get_JID_from_bare(const string bare){

		Roster::iterator it;
		Roster* roster= ptr_cpclient->get_roster();
		JID j;
		for (it=(*roster).begin();it!=(*roster).end();it++){
				j.setJID((*it).first);
				if ( j.bare() == bare ){ return j;}
		}


}

MessageSession* Core::create_session(JID jid){

		MessageSession* session = new MessageSession(ptr_cpclient->get_client(),jid);
		return session;


}

////////////////////////////////////////
//----------> CpClient

void CpClient::define_client(Client* cl){
	ptr_client=cl;
}

Roster* CpClient::get_roster(){
	return ptr_client->rosterManager()->roster();
}

MessageSession* CpClient::get_session_from_bare(const string bare){
		vector<MessageSession*>::iterator it;

		for (it=session_list.begin();it<session_list.end();it++){
				if ((*it)->target().bare() == bare) return *it; 
		}
		
		return 0;

}

void CpClient::add_session(MessageSession* session){
		session_list.push_back(session);	
}






void CpClient::register_core(Core* co){
	ptr_client->registerConnectionListener( co );
	ptr_client->registerMessageSessionHandler( co, 0 );
	//ptr_client->registerMessageHandler( co);
	ptr_client->registerPresenceHandler( co );
	ptr_client->rosterManager()->registerRosterListener(co);
		
}

void CpClient::register_session(MessageSession* session){
	ptr_client->registerMessageSession(session);
}

void CpClient::launch_connect(){
	ptr_client->connect(false);
	pthread_t xmpp_thread;		
	pthread_create(&xmpp_thread, NULL, connect_thread,(void *) ptr_client);	

}

void CpClient::launch_disconnect(){
		//ptr_client->disconnect(ConnUserDisconnected); 
}

Client* CpClient::get_client(){

	return ptr_client;
}
		
void* connect_thread(void *objet){
		
		//((Client*)objet)->connect(false);
		while (true){
			((Client*)objet)->recv(400);
		}
		return NULL;
}
