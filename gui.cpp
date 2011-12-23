#include <string>
#include "interface.h"


int main(){

terminal xterm;
output sortie(xterm.hauteur,xterm.largeur);
input entree(xterm.hauteur,xterm.largeur);


sortie.se_dessiner();
entree.se_dessiner();

string annonce=".: Bienvenue sur cptalk :.";
sortie.annoncer(annonce);

//sortie.affichage();
while(true){

	sortie.refresh();
	entree.refresh();

	entree.editer(sortie,true);
	
	sortie.raz();
	sortie.affichage();
	
	entree.raz();
	update_panels();
}


endwin();
return 0;

}


