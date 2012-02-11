#include "Linker.h"
#include "IO.h"
#include "ICore.h"
#include "XMPP.h"

Linker::Linker(){
}

Linker::~Linker(){}

////////////////////////////////////////
//----------> Linker
void Linker::command_parser(Line& line){

	vector<string> command_tokens;
	
	Line l1("");								  
	char h_command;
	unsigned int i=1;
	unsigned int found;
	string str_temp;
	
	h_command=line.content[0];




	if ( h_command == '$' ) {
		line.type_content = message;
		
		found=line.content.find_first_of(' ',i);
		str_temp=line.content.substr(i,found-1);
		command_tokens.push_back(str_temp);
		
		//l1.content=str_temp;								  
		//command_router(l1);
		string bare_jid = str_temp;
		string body = "";
		
		if ( found != string::npos ) { 
			body = line.content.substr(found+1,line.content.size()-1-found);
		}

	
		// verify there's a bare_jid with that existing name (maybe reusing a part of the complete function?)
		if ( find_from_vector(bare_jid , roster_choice) ) {
			l1.content="The JID you're sending a message to belongs to your roster list!";								  
			command_router(l1);
			send_message(bare_jid,body);
		} else {
			l1.content="This JID doesn't exist in your roster or is not connected!";								  
			command_router(l1);
		}




	} else if ( h_command == '/' ) {

		line.type_content = command;
		command_router(l1);
		l1.content="Info: the input strings has been parsed by the system!";								  
		command_router(l1);

  		
		found=line.content.find_first_of(' ',i);
		
			while ( found != string::npos ){
			
				str_temp=line.content.substr(i,found-i);
				command_tokens.push_back(str_temp);
 			
				i=found+1;
				found=line.content.find_first_of(' ',found+1);
			}

		str_temp=line.content.substr(i,found);
		command_tokens.push_back(str_temp);

		command_analyser(command_tokens);

	} else {

		command_router(l1);
		l1.content="Warning: the following string can't be parsed by the system!";								  
		command_router(l1);
		command_router(line);
	}

	 // parse the line
}

void Linker::command_analyser(vector<string> line_tokens){
	
	Line l("");
	

	if ( line_tokens[0] == "connect" ){
			l.content="Connecting...";
			command_router(l);
			XMMP_connect();
	}
	else if ( line_tokens[0] == "disconnect"){
			l.content="Disconnecting...";
			command_router(l);
	}
	else if ( line_tokens[0] == "list"){
		if ( line_tokens[1] == "roster"){
			l.content="Listing...";
			command_router(l);
			list_roster();

		}		
		if ( line_tokens[1] == "sessions"){
			l.content="Listing...";
			command_router(l);
			list_sessions();

		}
	}




}

void Linker::command_router(Line& line){

ptr_output->add_history(line);
set_token(true); // does input must let oupout print?

} // route the command to the output

bool Linker::find_from_vector(string s, vector<string> list){
		unsigned int i;

		for(i=0;i<list.size();i++){
			if( s == list[i] ) {
					return true;
			}
		}

		return false;


}

void Linker::send_message(string bare_jid,string body){

		MessageSession* session = ptr_core->get_session_from_bare(bare_jid);


		// verify there's a session existing with that roster
		if ( session != 0 ) {
				//Line l("Session number with this jid: " + session->threadID());
				//command_router(l);	
				session->send(body);
				Line l(bare_jid + " <- " + body);
				command_router(l);	
		} else {
				Line l("No session exists for this JID, cptalk will create one!");
				command_router(l);	
				ptr_core->create_session(bare_jid)->send(body);
				l.content=bare_jid + " <- " + body;
				command_router(l);	
				//l=ptr_core->get_JID_from_bare(bare_jid)->full();
				//command_router(l);	

				
				
		}



}

void Linker::register_clients(Output& output, Input& input, Core* core){
	
		ptr_output=&output;
		ptr_input=&input;
		ptr_core=core;
}

unsigned int& Linker::get_output_index(){
		return ptr_output->get_index();
}

void Linker::output_lineup(){
	if ( get_output_index() > 0 ){
		output_reset();
		ptr_output->print_history(--get_output_index());	
		output_refresh();
	}

}

void Linker::output_linedown(){
		
	if ( get_output_index() < ptr_output->get_history_size() ){
		output_reset();
		ptr_output->print_history(++get_output_index());		
		output_refresh();
	}

}
		
void Linker::output_refresh(){
	ptr_output->refresh();
	//ptr_output->refresh_terminal();
}

void Linker::output_reset(){
	ptr_output->reset();
}
		
void Linker::output_print_last_n(unsigned int n){
		
		ptr_output->print_history_last_n(n);
		output_refresh();
}

void Linker::output_print_history(unsigned int i){
		ptr_output->print_history(i);
		output_refresh();
}
		
unsigned int Linker::get_output_window_writable_height(){
		if (ptr_output->get_window_height() > 3){
		return ptr_output->get_window_height()-3;}
		else { return 0;}
}

void Linker::action_router(){
		ptr_input->edit();
}

void Linker::set_token(bool token){
	action_token=token;
}

bool Linker::get_token(){
	return action_token;
}

void Linker::XMMP_connect(){
		ptr_core->launch_connect();
}

void Linker::list_roster(){
		ptr_core->list_roster();
}

void Linker::list_sessions(){
		ptr_core->list_sessions();
}

void Linker::update_roster_choice(vector<string> list_roster){
		roster_choice = list_roster;
		ptr_input->update_roster_choice(list_roster);
}


