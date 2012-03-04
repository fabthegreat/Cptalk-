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


#include "IO.h"
#include "Linker.h"


Terminal::Terminal(){

// initialisation du screen principal		
	initscr();
	cbreak();// idem que raw() renvoit les caractères les uns après les autres sans attendre de CR
	echo();//ecris ce qui est tapé

// attribution du stdscr

	this->window=stdscr;
	getmaxyx(this->window,height,width);

}

Terminal::~Terminal(){
	endwin();
}


IO::IO(unsigned int a,unsigned int b)
:height(a),width(b),print_index(0)
{
}

IO::~IO(){}

Output::Output(Terminal& term)
:IO(term.height-3,term.width){
}

Output::~Output(){}

Input::Input(Terminal& term)
:IO(term.height,term.width){

	commands_choice.push_back("connect");
	commands_choice.push_back("disconnect");
	commands_choice.push_back("list roster");
	commands_choice.push_back("list sessions");
}

Input::~Input(){}

void Terminal::refresh(){ 
	update_panels();
}


////////////////////////////////////////
//----------> IO 
void IO::refresh(){
	wrefresh(window);

}

void IO::reset(){
	werase(window);
	draw();
}


void IO::add_history(Line l){
	history.push_back(l);
	//display.push_back(l);
	push_to_display(l,width - 2);
}

void IO::print_line(Line l, unsigned int i){
	char *a = new char [l.content.size()+1];
	strcpy (a, l.content.c_str());
	mvwprintw(window,i,1,"%s",a);
	delete a;
}

void IO::push_to_display(Line l, unsigned int w){
	
	Line pushed_line = l;
	pushed_line.content = l.content;

	unsigned int i=0;
	unsigned int rmn = l.content.size();	
	


	while ( rmn > w ){
			pushed_line.content = l.content.substr(i,w);
			display.push_back(pushed_line);
			i += w;
			rmn -= w;
	}

	if ( rmn <= w ){
			pushed_line.content = l.content.substr(i,w);
			display.push_back(pushed_line);
	}


}

unsigned int& IO::get_index(){
	return print_index;
}


unsigned int IO::get_history_size(){
		return display.size();
}

unsigned int IO::get_window_height(){
		return height;
}

unsigned int IO::get_start_index(unsigned int final_index,unsigned int line_number){
		if ( final_index < line_number ) { return 0;} else { return (final_index-line_number); } 
}	


unsigned int IO::get_final_index(unsigned int start_index,unsigned int line_number){
			return min(display.size(),start_index+line_number);
}	

void IO::register_terminal(Terminal& terminal){
	ptr_terminal=&terminal;
}

void IO::refresh_terminal(){

		ptr_terminal->refresh();
}

////////////////////////////////////////
//----------> Output
void Output::draw(){

	window=newwin(height,width,0,0);
	box(window,0,0);
	panel= new_panel(window);

}

void Output::print_history(unsigned int i){

	unsigned int i_print=1;
	unsigned int it;
	unsigned int ps; //point start
	unsigned int pf; //point final

	ps=max((unsigned int)0,min(i, display.size()-1));
	pf=get_final_index(ps,height-2);
	print_index=ps;	

	for ( it=ps ; it < pf; it++ ){
			print_line(display[it].content,i_print++);
	}


}

void Output::print_history_last_n(unsigned int n){

	unsigned int i_print=1;
	unsigned int it;
	unsigned int ps; //point start
	unsigned int pf; //point final

	pf=display.size();
	ps=get_start_index(pf-1,n);
	print_index=ps;	

	for ( it=ps ; it < pf; it++ ){
			print_line(display[it].content,i_print++);
	}


}




////////////////////////////////////////
//----------> Input
 // gather all input element and send it etiher to linker or to itself
 //void Input::char_action_launcher(){}

void Input::set_timeout(unsigned int t_out){
	
	timeout=t_out;
	wtimeout(window, timeout);
}



void Input::draw(){
	window=newwin(3,width,height-3,0);
	keypad(window, TRUE);
	box(window,0,0);
	panel= new_panel(window);
	mvwprintw(window,1,1,"> ");
	set_timeout(8); //release the input in order something else write on the output
}

void Input::register_linker(Linker& linker){
ptr_linker=&linker;
}


void Input::edit(){
		
		unsigned int i=0; //position of the char
		unsigned int ip=0; //position of the cursor
		unsigned int w = width - 5;

		string s; // will be sent to the linker object
		string sp;

		while( char_analysis(mvwgetch(window,1,ip+3),i,s) ){ //giving the hand to the input during timeout

				// if i>input total length then print from i-length
				sp = s;
				ip = i;
				
				if ( i > w ){
					sp = s.substr(i-w, w); 
					ip = w;
					
				} else {
					sp = s.substr(0, w);
				}

					print_string(sp);

				ptr_linker->XMMP_recv(400); // receiving datas from the server during 5ms
				
				if ( ptr_linker->get_token() ){
						ptr_linker->output_reset();
						ptr_linker->output_print_last_n(ptr_linker->get_output_window_writable_height()); 
						ptr_linker->set_token(false);
						ptr_linker->output_refresh();
				}
		}
		
		if ( s.empty() == false ) {
			Line l(s);
			add_history(l);
			print_index=display.size(); // print_index is set to the last member of history
			ptr_linker->command_parser(l);
		}
}		

bool Input::char_analysis(int c,unsigned int& i, string& s){
		
		if (c == KEY_LEFT){
				if ( i>0 ){i--;}
				return true;
		}
		else if (c == KEY_RIGHT){
				if ( i<s.size() ){i++;}
				return true;
		}
		else if (c == KEY_BACKSPACE){
				if ( i>0 ){
					i--;
				}
				s.erase(i,1);
				return true;
		}
		else if (c == KEY_DC){
				s.erase(i,1);
				return true;
		}
		else if (c == KEY_UP){
				if ( print_index>0 ){
					s=display[--print_index].content;
					i=0; // replace the cursor on the first caracter of the string
				}
				return true;
		}
		else if (c == KEY_DOWN){
				if ( display.empty() != true) {
					if ( print_index < display.size()-1 ){
						s=display[++print_index].content;
						i=0; // replace the cursor on the first caracter of the string
					}
				}
				return true;
		}
		else if (c == KEY_PPAGE){
				ptr_linker->output_lineup();
				return true;
		
		}
		else if (c == KEY_NPAGE){
				ptr_linker->output_linedown();
				return true;
		}
		else if (c == '\t'){
				return complete(s,i);

				//return true;
		
		}
		else if (c == '\n') {
				reset(); // cancel the CR effect of '\n'
				refresh(); // cancel the CR effect of '\n'
				return false;}
		
		else if (c == ERR) {
				return true;}

		s.insert(i++,1,c);
		return true;


}

bool Input::complete(string& s,unsigned int& index){

		vector<string> complete_list;
		vector<string> match_list; // list of matching commands



		unsigned int i;
		char h_command;

		for(i=0;i<s.size()+1;i++){
				if ( s[s.size()-i] == '/' ){
					s = s.substr(s.size()-i+1,i);
					complete_list = commands_choice; // if a '/' is detected you try to complete a command 
					h_command='/';
				} else if ( s[s.size()-i] == '$' ){
					s = s.substr(s.size()-i+1,i);
					complete_list = roster_choice; // if a '$' is detected you try to complete a roster 
					h_command='$';
				}
		}

		unsigned int nb_commands=0;
		unsigned int found;
		string found_command;


		Line l("");
		l.content="Available tokens: ";

		for(i=0;i<complete_list.size();i++){
			found = complete_list[i].find(s);	
			if(found == 0) {
					nb_commands++;
					l.content += " " + complete_list[i];
					found_command = complete_list[i];
					match_list.push_back(found_command);
			}
		}
		
		if ( nb_commands > 1 ) {
				//ptr_linker->command_router(l);
			s = h_command + s;

			unsigned int ml_count = 1;
			int c = '\t';
			while ( (c == ERR) || (c == '\t') ){

				if ( c == '\t' ) { 
				s = h_command + match_list[ml_count++];
				print_string(s);	

					if ( ml_count == match_list.size() ) ml_count=0;
				}
			c = mvwgetch(window,1,s.size()+3);
			}
		index = s.size();
		return 	char_analysis(c, index, s);


		} else if ( nb_commands == 0 ){
			s = h_command + s;
		} else if ( nb_commands == 1 ) {
			s = h_command + found_command + " ";
		} 

		index=s.size();

		return true;


}




void Input::print_string(string s){
		char *a = new char [s.size()+1];
		strcpy (a, s.c_str());
		reset();
		mvwprintw(window,1,3,"%s",a);
		delete a;
}

void Input::update_roster_choice(vector<string> list_roster){
	roster_choice = list_roster;

}

