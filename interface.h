#include "Core.h"
#include <ncurses.h>
#include <panel.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
/**
|-----|		   |------|		  |------|
|INPUT|------->|PARSER|------>|OUTPUT|
|-----|		   |------|		  |------|
				  |
				  |
				  |
			    |----|
			    |CORE|
			    |----|
**/

using namespace std;

// Forward declaration for dialog between Linker and ICore_XMPP
class Linker;
class Core;
class Input;
class Output;
class CpClient;



// amené a être le même

enum Type_content {all,command,message,announce};
enum Route {route_output,route_XMPP};
/*enum command_value {connect,disconnect,list_r};*/


class Line {
	public:
		Line(string s, Type_content tp=all);
		~Line();
	
		string content;
		Type_content type_content;
};

typedef vector<Line> Buffer;

class Command {
	public:
		Command();
		~Command();

		//parser command?
		
	private:
		Route route;
		string content;
};


class Terminal {
	public:
		Terminal();
		~Terminal();
		
		void refresh();
		// pour l instant publique
		unsigned int height; //nb_lignes
		unsigned int width; //nb_colonnes


	private:
		WINDOW* window; // pointeur vers la fenetre concernee

};

// classe de base Input et Ouput
class IO {
		public:
			IO(unsigned int a, unsigned int b);
			~IO();

			virtual void draw()=0;
			virtual void refresh();
			virtual void reset();
			virtual void add_history(Line l);
			virtual void print_line(Line l,unsigned int i); //i: ligne d'affichage
			virtual unsigned int& get_index();
			virtual unsigned int get_history_size();
			virtual unsigned int get_window_height();
			void register_terminal(Terminal& terminal);
			void refresh_terminal();


			
		
		protected:		
			unsigned int height; //nb_lignes
			unsigned int width; //nb_colonnes
			
			unsigned int get_start_index(unsigned int final_index,unsigned int line_number);
			unsigned int get_final_index(unsigned int start_index,unsigned int line_number);

			unsigned int print_index; //register the index printed

			WINDOW* window; // pointeur vers la fenetre concernee
			PANEL* panel;
			Terminal* ptr_terminal;

			Buffer history;
};


class Output : public IO {
	public:
		Output(Terminal& term);
		~Output();

		void draw();
		void print_history(unsigned int i);
		void print_history_last_n(unsigned int n); // print last n lines if possible

	private:
};


class Linker {
	public:
		Linker();
		~Linker();
			
		// Main controls
		void action_router();
		void set_token(bool token);
		bool get_token();
	

		// Treatment actions
		void command_parser(Line& line); // parser the line
		void command_analyser(vector<string> line_tokens);
		void command_router(Line& line); // route the command

		void register_clients(Output& output,Input& input, Core* core);

		// Ouput control
		unsigned int& get_output_index();
		unsigned int get_output_window_writable_height();
		void output_refresh();
		void output_reset();
		void output_lineup();
		void output_linedown();
		void output_print_last_n(unsigned int n);
		void output_print_history(unsigned int i);
		
		// Core control
		void XMMP_connect();
		void list_roster();
		void send_message(string bare_jid,string body);

		// Input offers
		void update_roster_choice(vector<string> list_roster);
	
	private:
		Core* ptr_core;
		Output* ptr_output;
		Input* ptr_input; //necessary to save input status each time something is printed
		
		bool action_token; //0 is output, 1 is input


};


class Input: public IO {
	public:
		Input(Terminal& term);
		~Input();

		void draw();
		void edit(); // gather all input element and send it either to linker or to itself
		bool char_analysis(int c, unsigned int& i,string& s);
		void complete(string& s,unsigned int& index);
		void register_linker(Linker& linker);
		void set_timeout(unsigned int t_out);
		void update_roster_choice(vector<string> list_roster);

	private:
		Linker* ptr_linker;
		
		void print_string(string s); //i: ligne d'affichage
		unsigned int timeout;
		
		vector<string> commands_choice;
		vector<string> roster_choice;


};

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
		MessageSession* get_session_from_bare(const string bare); //just a temp function to retrieve session id from a bare jid


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
		void register_session(MessageSession* session);
		void define_client(Client* cl);
		Roster* get_roster();
		MessageSession* get_session_from_bare(const string bare);
		void add_session(MessageSession* session);

	private:
		Client* ptr_client;
		vector<MessageSession*> session_list; 
};




