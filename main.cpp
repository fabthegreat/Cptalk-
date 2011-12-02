#include "Core.h"
#include <iostream>
#include <string>

using namespace gloox;


void *connect_thread(void *objet);
void start_commandmode();

int main() {

		std::cout << "######## Demarrage de cptalk v0 ########" << std::endl; 


		Core* core=new Core();
	 	core->connected=false;	

		JID jid( "bot@lutix.org/cptalk" );
		Client* client = new Client( jid, "fab99999" );
		client->registerConnectionListener( core );
		client->registerMessageSessionHandler( core, 0 );
		//client->connect(); 

		/** Exemple de Thread **/
		pthread_t my_thread;		
	
		/*void *thread_fnc(void *arg)**/
		
		pthread_create(&my_thread, NULL, connect_thread,(void *) client);	
		
		//pthread_join(my_thread,NULL);
		bool start=false;
		
		while ( start == 0 ) { 
		start=core->connected;
		}	
		
		start_commandmode();			
		return 0;
}

void start_commandmode(){
		std::cout << std::endl << "Mode commande de cptalk:" << std::endl;
		std::string commande;
		while(std::cin >> commande) {
		std::cout << "Vous avez entré une commande!" << std::endl;}
		


}

void *connect_thread(void *objet){
		((Client*)objet)->connect();


return NULL;

}


