#include "XMPP.h"
#include "IO.h"
#include "Linker.h"
#include "ICore.h"

#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/presencehandler.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/rosterlistener.h>
#include <gloox/rostermanager.h>

#include <iostream>
#include <string>

void start_XMPP(Core* core);
void start_interface(Core* core);

// function pointer for connection threading
//void* connect_thread(void *objet);

int main() {

		Core* core=new Core;
		start_XMPP(core);	
		start_interface(core);
		
		delete core;
		return 0;
}

void start_XMPP(Core* core) {

		
		core->connected=false;	

		JID jid( "bot@lutix.org/cptalk" );
		Client* client = new Client( jid, "fab99999" );

		CpClient* cpclient=new CpClient;
		cpclient->define_client(client); // look at the client object to be implemented
		// The observable adds an observer
		// when the client launches a signal, it informs the core that launches actions (slots)
		// but sometimes the core needs to control the client
		cpclient->register_core(core);
		core->register_cpclient(cpclient);

		//cpclient->launch_connect();
		
	
		
}




void start_interface(Core* core){

		std::cout << "Attente..." << std::endl;
		
		// Créer une fabrique/classe spécifique?
		Terminal xterm;	
		Input input(xterm);	
		Output output(xterm);		

		//Core core;
		Linker linker; 

		linker.register_clients(output,input,core);
		input.register_linker(linker);
		output.register_terminal(xterm);
		core->register_linker(linker);
		//Fin de fabrique?
		
		output.draw();
		input.draw();

		Line message_0("###########################");
		Line message_1("#    Welcome on cptalk    #");
		Line message_2("###########################");
		linker.command_router(message_0);
		linker.command_router(message_1);
		linker.command_router(message_2);

		output.print_history(0);

		while(true){

				output.refresh();
				input.refresh();

				//input.edit();

				linker.action_router();

				output.reset();
				input.reset();
				linker.output_print_last_n(linker.get_output_window_writable_height()); 

		}
}




