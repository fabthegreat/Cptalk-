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

		Line message_0("###########################");
		Line message_1("#    Welcome on cptalk    #");
		Line message_2("###########################");
		linker.command_router(message_0);
		linker.command_router(message_1);
		linker.command_router(message_2);

		output.print_history(0);

		while(true){

				output.refresh();
				input.refresh();
				xterm.refresh();

				input.edit();

				output.reset();
				input.reset();
				linker.output_print_last_n(linker.get_output_window_writable_height()); 

		}

		return 0;
}




