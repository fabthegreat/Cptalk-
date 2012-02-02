
#ifndef IO_H
#define IO_H
//
// Forward declaration for dialog between Linker and ICore_XMPP
class Linker;
class Core;
class Input;
class Output;
class CpClient;

// Headers include
#include "common.h"
#include <ncurses.h>
#include <panel.h>
#include <cstring>
#include <iostream>
#include <vector>

class Terminal {
	public:
		Terminal();
		~Terminal();
		
		void refresh();
		// pour l instant publique
		unsigned int height; //nb_lignes
		unsigned int width; //nb_colonnes


	private:
		WINDOW* window; // pointeur vers la fenetre concernee

};

// classe de base Input et Ouput
class IO {
		public:
			IO(unsigned int a, unsigned int b);
			~IO();

			virtual void draw()=0;
			virtual void refresh();
			virtual void reset();
			virtual void add_history(Line l);
			virtual void print_line(Line l,unsigned int i); //i: ligne d'affichage
			virtual unsigned int& get_index();
			virtual unsigned int get_history_size();
			virtual unsigned int get_window_height();
			void register_terminal(Terminal& terminal);
			void refresh_terminal();


			
		
		protected:		
			unsigned int height; //nb_lignes
			unsigned int width; //nb_colonnes
			
			unsigned int get_start_index(unsigned int final_index,unsigned int line_number);
			unsigned int get_final_index(unsigned int start_index,unsigned int line_number);

			unsigned int print_index; //register the index printed

			WINDOW* window; // pointeur vers la fenetre concernee
			PANEL* panel;
			Terminal* ptr_terminal;

			Buffer history;
};


class Output : public IO {
	public:
		Output(Terminal& term);
		~Output();

		void draw();
		void print_history(unsigned int i);
		void print_history_last_n(unsigned int n); // print last n lines if possible

	private:
};

class Input: public IO {
	public:
		Input(Terminal& term);
		~Input();

		void draw();
		void edit(); // gather all input element and send it either to linker or to itself
		bool char_analysis(int c, unsigned int& i,string& s);
		void complete(string& s,unsigned int& index);
		void register_linker(Linker& linker);
		void set_timeout(unsigned int t_out);
		void update_roster_choice(vector<string> list_roster);

	private:
		Linker* ptr_linker;
		
		void print_string(string s); //i: ligne d'affichage
		unsigned int timeout;
		
		vector<string> commands_choice;
		vector<string> roster_choice;


};

#endif /* IO_H */
