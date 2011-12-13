#include "interface.h"

terminal::terminal(){

// initialisation du screen principal		
	initscr();
	cbreak();// idem que raw() renvoit les caractères les uns après les autres sans attendre de CR
	echo();//ecris ce qui est tapé

// attribution du stdscr

	this->fenetre=stdscr;
	getmaxyx(this->fenetre,hauteur,largeur);

}

terminal::~terminal(){
	endwin();
}

//////// INPUT et OUTPUT /////////////////

//////////////////////////////////////////
//---------->Constructeurs et destructeurs
output::output(int a, int b)
:hauteur(a-3),largeur(b),mode(all),indice_affichage(0){}

output::~output(){

}



input::input(int a, int b)
:hauteur(a),largeur(b),mode(all),indice_affichage(0){
}

input::~input(){
}


////////////////////////////////////////
//----------> Affichage des Panels
void input::se_dessiner(){
	fenetre=newwin(3,largeur,hauteur-3,0);
	keypad(fenetre, TRUE);
	box(fenetre,0,0);
	panel= new_panel(fenetre);
	mvwprintw(fenetre,1,1,"> ");

}

void output::se_dessiner(){

	fenetre=newwin(hauteur,largeur,0,0);
	box(fenetre,0,0);
	panel= new_panel(fenetre);

}
////////////////////////////////////////
//----------> Fonctions de MAJ
void output::refresh(){

	wrefresh(fenetre);
}

void output::raz(){

		werase(fenetre);
		this->se_dessiner();
}

void input::refresh(){

	wrefresh(fenetre);
}

void input::raz(){

		werase(fenetre);
		this->se_dessiner();
}




////////////////////////////////////////
//----------> Affichage des lignes
void output::affichage(){
		
		int j=0;
		for(unsigned int i=max(0,(int)historique.size()-hauteur+2);i<historique.size();i++){
			
			
			if ( (historique[i].categorie == mode) || (mode == all)){	
				char *a = new char [historique[i].str_ligne.size()+1];
				strcpy (a, historique[i].str_ligne.c_str());
			
				mvwprintw(fenetre,++j,1,"%s",a);
				delete a;
			}
		}
		


}

void input::affichage(string& s){
		
			
			char *a = new char [s.size()+1];
			strcpy (a, s.c_str());
			raz();	
			mvwprintw(fenetre,1,3,"%s",a);
			delete a;
		


}



////////////////////////////////////////
//----------> Ajout dans les historiques
void output::ajout_ligne(ligne& l){

historique.push_back(l);

}


void input::ajout_ligne(ligne& l){

historique.push_back(l);

}





////////////////////////////////////////
//----------> Spécifique INPUT
void input::editer(output& out, bool print){

		
		int b; // char entré
		int i=0; //position du curseur
		string s;
		ligne l;

		// chaque caractere tapé est analysé un par un:
		// caractère normal: copié dans la chaine à l indice du curseur
		// caractère spécial: déplacement du curseur, suppression ou insertion de caractere dans la chaine
		//
		//
		while ( b != '\n' ){
		
		b=mvwgetch(fenetre,1,i+3); //reception basique d'un caractere
		
		analyse_inputchar(b,s,i); // analyse du caractere, transformation de la chaine et retour de l'indice de position 	
		// penser à mettre un const b	
		//reafficher la string
		
		

		}
		
		// detecter ligne vide et parsage de la string			
	 	if (!s.empty()){
		bool tf;
		tf=analyse_commande(s,l);
		ajout_ligne(l);
		indice_affichage=historique.size();


				
		if ( (print == true) && (s.size()!=0) ) out.ajout_ligne(l);
		}
}


void input::analyse_inputchar(int b, string& s, int& i){
		
		if (b == KEY_LEFT){
		i=max(0,i-1);
				//s.insert(i++,1,b);
		}
		else if (b == KEY_RIGHT){
		
				int taille=s.size();
				i=min(taille,i+1);
		
		}
		else if (b == KEY_BACKSPACE){
				i=max(0,i-1);
				s.erase(i,1);
				affichage(s);
		}
		else if (b == KEY_DC){
				s.erase(i,1);
				affichage(s);
		}
		else if (b == KEY_UP){
				if (!historique.empty()){	
						indice_affichage=max(0,indice_affichage-1);
						s=historique[indice_affichage].str_ligne;
						affichage(s);
				}
		}		
		else if (b == KEY_DOWN){
				if (!historique.empty()){	
						int taille=historique.size()-1;
						indice_affichage=min(taille,indice_affichage+1);
						s=historique[indice_affichage].str_ligne;
						affichage(s);
				}
		}		
		else if (b == '\n'){}
		else { 
				s.insert(i++,1,b);
				affichage(s);
		}
		
		

}


bool input::analyse_commande(string& s,ligne& l){


	l.str_ligne=s;
	string cmd;

	detection_commande(s, cmd);

	if (cmd.empty()){
		l.categorie=message; //provisoirement
	return true;
	}
	else if(cmd=="/message"){
		l.str_ligne="Detection d'une commande message";
		l.categorie=commande; //provisoirement
	return true;
	}
	else{
	l.categorie=all; //provisoirement
	return false;
	}





}

void input::detection_commande(string& s,string& commande){
	
	size_t pos_vide;	
	
	if (s[0]=='/'){
		
		pos_vide=s.find_first_of(" ");
		if (pos_vide!=s.npos){	
			commande=s.substr(0,pos_vide);}
		else{
			commande=s.substr(0,s.size());}
		}

		



}


