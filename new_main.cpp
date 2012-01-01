#include "interface.h"
#include <iostream>
#include <string>



int main() {

		std::cout << "Attente..." << std::endl;
		
		//Créer une fabrique/classe spécifique?
		Terminal xterm;	
		Input input(xterm);	
		Output output(xterm);		
		ICore_XMPP icore_xmpp;
		Linker linker; 

		linker.register_clients(output,icore_xmpp);
		input.register_linker(linker);
		icore_xmpp.register_linker(linker);
		//Fin de fabrique?

		output.draw();
		input.draw();

		Line l1("Bienvenue sur Cptalk");
		linker.command_router(l1);

		output.print_history(0);

		while(true){

				output.refresh();
				input.refresh();
				xterm.refresh();

				input.edit();

				//output.reset();
				input.reset();
				linker.output_print_history(0);
				//output.print_history(0);

		}

		return 0;
}




