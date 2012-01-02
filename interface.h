#include <ncurses.h>
#include <panel.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
/**
|-----|		   |------|		  |------|
|INPUT|------->|PARSER|------>|OUTPUT|
|-----|		   |------|		  |------|
				  |
				  |
				  |
			    |----|
			    |CORE|
			    |----|
**/

using namespace std;

// Forward declaration for dialog between Linker and ICore_XMPP
class Linker;
class ICore_XMPP;
class Input;
class Output;



// amené a être le même

enum Type_content {all,message,announce};
enum Route {route_output,route_XMPP};


class Line {
	public:
		Line(string s, Type_content tp=all);
		~Line();
	
		string content;
		Type_content type_content;
};

typedef vector<Line> Buffer;

class Command {
	public:
		Command();
		~Command();

		Route destination;
		string content;

	private:
};


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
		
		protected:		
			unsigned int height; //nb_lignes
			unsigned int width; //nb_colonnes
			
			unsigned int get_start_index(unsigned int final_index,unsigned int line_number);
			unsigned int get_final_index(unsigned int start_index,unsigned int line_number);

			unsigned int print_index; //register the index printed

			WINDOW* window; // pointeur vers la fenetre concernee
			PANEL* panel;

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


class Linker {
	public:
		Linker();
		~Linker();
			
		void command_parser(Line& line); // parser the line
		void command_analyser(Line& line);
		void command_router(Line& line); // route the command

		void register_clients(Output& output, ICore_XMPP& icore_xmpp);

		unsigned int& get_output_index();
		unsigned int get_output_window_writable_height();
		void output_refresh();
		void output_reset();
		void output_lineup();
		void output_linedown();
		void output_print_last_n(unsigned int n);
		void output_print_history(unsigned int i);
	
	private:
		ICore_XMPP* ptr_icore_xmpp;
		Output* ptr_output;

};


class Input: public IO {
	public:
		Input(Terminal& term);
		~Input();

		void draw();
		void edit(); // gather all input element and send it either to linker or to itself
		bool char_analysis(int c, unsigned int& i,string& s);
		void register_linker(Linker& linker);

	private:
		Linker* ptr_linker;
		void print_string(string s); //i: ligne d'affichage
};

class ICore_XMPP {

	public:
		ICore_XMPP();
		~ICore_XMPP();

		void register_linker(Linker& linker);

	private:
		Linker* ptr_linker;

};


