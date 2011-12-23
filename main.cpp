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
		
		Core* core=new Core(xterm,"bot@lutix.org/cptalk","fab99999");
		core->connected=false;	

				
		/** Thread de connexion**/
		pthread_t my_thread;		
	
		/*void *thread_fnc(void *arg)**/
		//thread pour la connexion en tache de fond	
		pthread_create(&my_thread, NULL, connect_thread,(void *)&core->client);	
		
		// Chargement de l'interface
		interface(core);	
		
		return 0;
}


void *connect_thread(void *objet){
		
		while (true){
			((Client*)objet)->connect(false);
			((Client*)objet)->recv(500); 
			// se connecte au serveur toutes les 0.5 secondes
			// => diminue la charge CPU
		}
		return NULL;
}


void interface(Core* core){

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
