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

// amené a être le même
typedef vector<string> buffer;

class Terminal {
	public:
		Terminal();
		~Terminal();
		
		// pour l instant publique
		unsigned int height; //nb_lignes
		unsigned int width; //nb_colonnes


	private:
		WINDOW* window; // pointeur vers la fenetre concernee

};

// classe de base Input et Ouput
class IO {
		public:
			IO(unsigned int a, unsigned  int b);
			~IO();

			virtual void draw()=0;
		
			unsigned int height; //nb_lignes
			unsigned int width; //nb_colonnes

			WINDOW* window; // pointeur vers la fenetre concernee
			PANEL* panel;

};

class Output : public IO {
	public:
		Output(Terminal& term);
		Output(Output& out);
		~Output();

		void draw();

	private:


};


class Linker {
	public:
		Linker(Output& o);
		~Linker();
			
	private:
		Output& out;
};


class Input: public IO {
	public:
		Input(Terminal& term, Linker& l);
		~Input();

		void draw();
		
	private:
		Linker& link;
};




