#include <string>
#include "interface.h"


int main(){

terminal xterm;
output sortie(xterm.hauteur,xterm.largeur);



for (int i=0;i<sortie.hauteur;i++){
string s="salut"+i;
sortie.ajout_ligne(s);
}


sortie.affichage();



update_panels();
doupdate();

getch();

return 0;

}



void test_c(){		
WINDOW *fenetres[2];
PANEL *panels[2];
char commande[1000];


int max_lin,max_col;

initscr();
cbreak();
echo();

getmaxyx(stdscr,max_lin,max_col);

// newwin(nb_ligne,nb_colonnes,depart_ligne,depart_colonne);
fenetres[0]=newwin(max_lin-3,max_col,0,0);
fenetres[1]=newwin(3,max_col,max_lin-3,0);


//wborder(fenetres[0],' ',' ',' ','#',' ',' ',' ',' ');
box(fenetres[0],0,0);
box(fenetres[1],0,0);
//box(fenetres[1],0,0);

panels[0]= new_panel(fenetres[0]);
panels[1]= new_panel(fenetres[1]);



mvwprintw(fenetres[1],1,1,"> ");


update_panels();

doupdate();


while(true){

wrefresh(fenetres[0]);
mvwgetstr(fenetres[1],1,3,commande);
mvwprintw(fenetres[0],1,1,"%s",commande);


}

getch();

endwin();
}

