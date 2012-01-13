#include "interface.h"
#include <iostream>
#include <string>

void start_XMPP(Core* core);
void start_interface(Core* core);

// function pointer for connection threading
void* connect_thread(void *objet);

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

		//Loading client module
		// The observable adds an observer
		// when the client launches a signal, it informs the core that launches actions (slots)
		client->registerConnectionListener( core );
		client->registerMessageSessionHandler( core, 0 );
		client->registerPresenceHandler( core );
		client->rosterManager()->registerRosterListener(core);
		
		/** Connexion thread**/
		pthread_t xmpp_thread;		
		
		pthread_create(&xmpp_thread, NULL, connect_thread,(void *) client);	
		
}


void* connect_thread(void *objet){
		
		while (true){
			((Client*)objet)->connect(false);
			((Client*)objet)->recv(400);
		}
		return NULL;
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




