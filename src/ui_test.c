# include <ncurses.h>

int main(int argc, char ** argv){

    // Inicializa la pantalla
    // Configura memoria y limpia la pantalla
    initscr();

    // Posicion del cursor
    int x, y;
    x = y = 5;

    // Mueve el cursor a una ubicacion especificada
    move(y, x);
    
    // Imprime una string en la ventana
    printw("Hola mundo");

    // Refresca la pantalla para que aparezca lo que esta en memoria
    refresh();

    // Retorna el valor int del key del user input
    getch();

    // Libera la memoria y cierra ncurses
    endwin();

    return 0;
}