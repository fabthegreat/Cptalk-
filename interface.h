#include "Core.h"
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
class Core_XMPP;
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

		//parser command?
		
	private:
		Route route;
		string content;
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


class Linker {
	public:
		Linker();
		~Linker();
			
		// Main controls
		void action_router();
		void set_token(bool token);
		bool get_token();

		// Treatment actions
		void command_parser(Line& line); // parser the line
		void command_analyser(vector<string> line_tokens);
		void command_router(Line& line); // route the command

		void register_clients(Output& output,Input& input, ICore_XMPP* icore_xmpp);

		// Ouput control
		unsigned int& get_output_index();
		unsigned int get_output_window_writable_height();
		void output_refresh();
		void output_reset();
		void output_lineup();
		void output_linedown();
		void output_print_last_n(unsigned int n);
		void output_print_history(unsigned int i);

		// Input control
	
	private:
		ICore_XMPP* ptr_icore_xmpp;
		Output* ptr_output;
		Input* ptr_input; //necessary to save input status each time something is printed
		
		bool action_token; //0 is output, 1 is input


};


class Input: public IO {
	public:
		Input(Terminal& term);
		~Input();

		void draw();
		void edit(); // gather all input element and send it either to linker or to itself
		bool char_analysis(int c, unsigned int& i,string& s);
		void register_linker(Linker& linker);
		void set_timeout(unsigned int t_out);

	private:
		Linker* ptr_linker;
		void print_string(string s); //i: ligne d'affichage
		unsigned int timeout;


};

class Core_XMPP {

	public:
		void attribute_linker(Linker& linker);
		void launch_output_refresh();
		
		// set of function for ICore_XMPP implementation
		//
		void send_line(Line line);

	private:
		Linker* ptr_linker;

};

class Core: public ICore_XMPP {
	public:
		void register_linker(Linker& linker);
		
		void onConnect();
		bool onTLSConnect(const CertInfo& info);


	private:
		Core_XMPP core_XMPP; //implementation

};
