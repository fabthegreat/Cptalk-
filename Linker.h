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

		// Global controls
		void get_and_push(int t, bool recv = true); // get datas from server and push to output
	

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
		void urgent_warning(Line l); // to use with care only with important messages that can't wait for server response

		// Input control
		void input_refresh();
		void input_reset();
		
		// Core control
		void XMMP_connect();
		void XMMP_disconnect();
		void XMMP_recv(int t);
		void lock_roster(string bare_jid);
		void unlock_roster();
		void list_roster();
		void list_sessions();
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
		string locked_roster;


};


#endif
