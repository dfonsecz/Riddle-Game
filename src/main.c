#include <ncurses.h>
#include "../include/menu.h"

int main() {
    initscr(); // inicializar ventana de ncurses
    noecho(); // deshabilitar echo de caracteres
    cbreak(); // recibe cada tecla que se presiona sin esperar a enter
    
    // Inicializar el menú principal
    menuWin();
    
    // Limpiar pantalla
    endwin();
    return 0;
}