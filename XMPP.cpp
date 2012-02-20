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
		write_string("You have received a status update of: " + item.jid() + " (" + msg + ")");
		// some bugs with item.jid(), check caracters issues
		update_roster_choice();
}		

void Core::handleMessage(const Message& msg, MessageSession* session){
	write_string(session->target().bare() + " -> " + msg.body());
	// to debug
	//print_session_id(session->target().bare());
}

void Core::handleMessageSession(MessageSession* session){
	ptr_cpclient->register_session(session);
	session->registerMessageHandler(this);
	ptr_cpclient->store_session(session);
}


void Core::register_cpclient(CpClient* cpclient){
	ptr_cpclient=cpclient;
}


void Core::launch_connect(){
	if (connected==false){
		ptr_cpclient->launch_connect();
	}
	else {
		write_string("You\'re already connected!");
	}
}

void Core::recv(int t){
		ptr_cpclient->recv(t);

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
	//write_string("Session " +  ptr_cpclient->get_session_from_bare(bare)->threadID() + " already opened with ID: " + bare);
	return ptr_cpclient->get_session_from_bare(bare);
}

MessageSession* Core::create_session(const string bare){

		MessageSession* session = new MessageSession(ptr_cpclient->get_client(),bare);
		//session->setThreadID("session_" + bare);
		ptr_cpclient->store_session(session);
		ptr_cpclient->register_session(session);
		session->registerMessageHandler(this);
		
		write_string("A new chat session is created with JID: " + session->target().full());
		return session;


}

void Core::list_sessions(){
		unsigned int i;
		vector<MessageSession*> s_list;
		s_list=ptr_cpclient->get_session_list();
		
		for (i=0;i<s_list.size();i++){
			write_string("*" + s_list[i]->target().full() + " -> " + s_list[i]->threadID());
		}

}

////////////////////////////////////////
//----------> CpClient

void CpClient::define_client(Client* cl){
	ptr_client=cl;
}

Roster* CpClient::get_roster(){
	return ptr_client->rosterManager()->roster();
}

vector<MessageSession*> CpClient::get_session_list(){
	return session_list;
}

MessageSession* CpClient::get_session_from_bare(const string bare){
		vector<MessageSession*>::iterator it;

		for (it=session_list.begin();it<session_list.end();it++){
				if ((*it)->target().bare() == bare) {
				
				return *it; 
				}
		}
		
		return 0;

}

void CpClient::store_session(MessageSession* session){
		session_list.push_back(session);	
}



void CpClient::register_session(MessageSession* session){
	ptr_client->registerMessageSession(session);
}



void CpClient::register_core(Core* co){
	ptr_client->registerConnectionListener( co );
	ptr_client->registerMessageSessionHandler( co, 0 );
	//ptr_client->registerMessageHandler( co);
	ptr_client->registerPresenceHandler( co );
	ptr_client->rosterManager()->registerRosterListener(co);
		
}


void CpClient::launch_connect(){
	ptr_client->connect(false);

}

void CpClient::recv(int t){
	ptr_client->recv(t);
}

void CpClient::launch_disconnect(){
		//ptr_client->disconnect(ConnUserDisconnected); 
}

Client* CpClient::get_client(){

	return ptr_client;
}
		
