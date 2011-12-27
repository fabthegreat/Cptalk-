#include "interface.h"
#include <iostream>
#include <string>



int main() {

		std::cout << "Attente..." << std::endl;

		Terminal xterm;	
		Output output(xterm);		
		Linker linker(output); // declaration du linker, envoye les sorties à out
		Input input(xterm,linker);	

		output.draw();

		return 0;
}




