#include "interface.h"
#include "Core.h"
#include <iostream>
#include <string>

void start_XMPP();
void start_interface();
void *connect_thread(void *objet);

int main() {

		start_XMPP();	
		start_interface();
		return 0;
}

void start_XMPP() {

		
		Core_XMPP* core=new Core_XMPP;
		core->connected=false;	

		JID jid( "bot@lutix.org/cptalk" );
		Client* client = new Client( jid, "fab99999" );
		/** Chargement des module du client **/
		client->registerConnectionListener( core );
		client->registerMessageSessionHandler( core, 0 );
		client->registerPresenceHandler( core );
		client->rosterManager()->registerRosterListener(core);
		
		/** Thread de connexion**/
		pthread_t my_thread;		
	
		
		pthread_create(&my_thread, NULL, connect_thread,(void *) client);	
		
}


void *connect_thread(void *objet){
		
		while (true){
			((Client*)objet)->connect(false);
			((Client*)objet)->recv(400);
		}
		return NULL;
}

void start_interface(){

		std::cout << "Attente..." << std::endl;
		
		//Créer une fabrique/classe spécifique?
		Terminal xterm;	
		Input input(xterm);	
		Output output(xterm);		
		ICore_XMPP icore_xmpp;
		Linker linker; 

		linker.register_clients(output,icore_xmpp);
		input.register_linker(linker);
		icore_xmpp.register_linker(linker);
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
				xterm.refresh();

				input.edit();

				output.reset();
				input.reset();
				linker.output_print_last_n(linker.get_output_window_writable_height()); 

		}
}





