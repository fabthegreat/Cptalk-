#ifndef LINKER_H
#define LINKER_H
//
// Forward declaration for dialog between Linker and ICore_XMPP
class Core;
class Input;
class Output;

// Headers include
#include "common.h"
#include <vector>
#include <string>


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
		bool find_from_vector(string s, vector<string> list);
	
	private:
		Core* ptr_core;
		Output* ptr_output;
		Input* ptr_input; //necessary to save input status each time something is printed
		
		bool action_token; //0 is output, 1 is input
		vector<string> roster_choice;


};


#endif
