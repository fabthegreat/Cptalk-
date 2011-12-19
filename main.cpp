#include "Core.h"
#include <iostream>
#include <string>

using namespace gloox;

void interface(Core* core);
void *connect_thread(void *objet);
void start_commandmode();

int main() {

		std::cout << "######## Demarrage de cptalk v0 ########" << std::endl; 

		terminal xterm;	
		
		Core* core=new Core(xterm);
	 	core->connected=false;	

		JID jid( "bot@lutix.org/cptalk" );
		Client* client = new Client( jid, "fab99999" );
		/** Chargement des module du client **/
		client->registerConnectionListener( core );
		client->registerMessageSessionHandler( core, 0 );
		client->registerPresenceHandler( core );
      	client->rosterManager()->registerRosterListener(core);
		
		//RosterManager* liste_roster = new RosterManager(client);
		//liste_roster->registerRosterListener(core);		


		/** Thread de connexion**/
		pthread_t my_thread;		
	
		/*void *thread_fnc(void *arg)**/
		
		pthread_create(&my_thread, NULL, connect_thread,(void *) client);	
		
		////pthread_join(my_thread,NULL);
		//bool start=false;
		//while ( start == 0 ) { 
		interface(core);	
		//start=core->connected;
		//}	
		
		//start_commandmode();			
		return 0;
}


void *connect_thread(void *objet){
		((Client*)objet)->connect();
		return NULL;
}


void interface(Core* core){

//core->output sortie(xterm.hauteur,xterm.largeur);
//core->input entree(xterm.hauteur,xterm.largeur);


core->sortie.se_dessiner();
core->entree.se_dessiner();

string annonce="Bienvenue sur Cptalk";
core->sortie.annoncer(annonce);

//sortie.affichage();
while(true){

	core->sortie.refresh();
	core->entree.refresh();

	core->entree.editer(core->sortie,true);
	
	core->sortie.raz();
	core->sortie.affichage();
	
	core->entree.raz();
	update_panels();
	//doupdate();
}


endwin();

}
