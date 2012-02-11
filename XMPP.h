#ifndef XMPP_H
#define XMPP_H

class Linker;
class Core;
class Input;
class Output;
class CpClient;

#include "ICore.h"
#include <string>
#include "common.h"
#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>




class Core: public ICore_XMPP {
	public:
		bool connected;
		void register_linker(Linker& linker);
		void register_cpclient(CpClient* cpclient);

		void launch_output_refresh();
		void launch_output_reset();
		void send_line(Line line);
		void write_string(string s);
		
		void onConnect();
		bool onTLSConnect(const CertInfo& info);
		void handleRosterPresence(const RosterItem &item, const std::string &resource, Presence::PresenceType presence, const std::string &msg);
		void handleMessage(const Message& msg, MessageSession* session);
		void handleMessageSession(MessageSession* session);

		// Actions asked by any class having access to a Core
		void list_roster();
		void launch_connect();
		void launch_disconnect();
		void update_roster_choice();

		void print_session_id(const string bare); //just a temp function to retrieve session id from a bare jid
		void list_sessions(); //just a temp function to list all current sessions in use
		MessageSession* get_session_from_bare(const string bare); //just a temp function to retrieve session id from a bare jid
		MessageSession* create_session(const string bare);


	private:
		/*Core_XMPP core_XMPP; //implementation*/
		CpClient* ptr_cpclient;
		Linker* ptr_linker;

};



void* connect_thread(void *objet);

class CpClient {
	public:
		void launch_connect();
		void launch_disconnect();
		void register_core(Core* co);
		void define_client(Client* cl);

		Roster* get_roster();
		Client* get_client();
		vector<MessageSession*> get_session_list();

		MessageSession* get_session_from_bare(const string bare);
		void register_session(MessageSession* session);
		void store_session(MessageSession* session);

	private:
		Client* ptr_client;
		vector<MessageSession*> session_list; 
};


#endif
