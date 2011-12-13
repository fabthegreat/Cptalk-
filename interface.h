#include <ncurses.h>
#include <panel.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
/*#include <algorithm>	*/

using namespace std;

enum type_mode{all,message,presence,commande};

class ligne{
		public:
		string str_ligne;
		type_mode categorie;


		vector<ligne> cmdfilter_bystr(string s);
		vector<ligne> cmdfilter_bytype(int a);
	
		private:
		string destinataire;
};

// amené a être le même
typedef vector<ligne> buffer_in;
typedef vector<ligne> buffer_out;



class terminal {
	public:
		terminal();
		~terminal();



		int hauteur; //nb_lignes
		int largeur; //nb_colonnes
	private:
		WINDOW* fenetre; // pointeur vers la fenetre concernee

};

// peut etre faire de la classe terminal la classe parente des classes output et input....

class output {
	public:
		output(int a, int b);
		~output();
		
		int hauteur; // nb_lignes
		int largeur; // nb_colonnes
		
		void se_dessiner();
		void refresh();
		void ajout_ligne(ligne& l);
		void affichage();
		void raz();
		type_mode mode;


	private:
		WINDOW* fenetre; // pointeur vers la fenetre concernee
		PANEL* panel;
		buffer_out historique;
		int indice_affichage;


};

class input {
	public:
		input(int a, int b);
		~input();
		
		void se_dessiner();
		void refresh();
		void editer(output& out, bool print=true);
		void analyse_inputchar(int b, string& s, int& i);
		bool analyse_commande(string& s,ligne& l);
		void detection_commande(string& s,string& c);
		void ajout_ligne(ligne& l);
		void affichage(string& s);
		void raz();

		int hauteur; // nb_lignes
		int largeur; // nb_colonnes
		type_mode mode;

	private:
		WINDOW* fenetre; // pointeur vers la fenetre concernee
		PANEL* panel;
		buffer_in historique;
		int indice_affichage;
};



