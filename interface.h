#include <ncurses.h>
#include <panel.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
/*#include <algorithm>	*/

using namespace std;


typedef vector<string> buffer;


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
		void ajout_ligne(string& s);
		void affichage();
		void raz();



	private:
		WINDOW* fenetre; // pointeur vers la fenetre concernee
		PANEL* panel;
		buffer historique;
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
		void ajout_ligne(string& s);
		void affichage(string& s);
		void raz();

		int hauteur; // nb_lignes
		int largeur; // nb_colonnes

	private:
		WINDOW* fenetre; // pointeur vers la fenetre concernee
		PANEL* panel;
		buffer historique;
		int indice_affichage;
};


class ligne{
		public:
		string str_ligne;
		enum type_ligne{message,presence};

		vector<ligne> cmdfilter_bystr(string s);
		vector<ligne> cmdfilter_bytype(int a);
	

};

