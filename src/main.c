#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "../include/menu.h" // Incluye el archivo de cabecera que contiene la declaración de menuWin

int main() {
    // Inicializa ncurses
    initscr();
    noecho();
    curs_set(0);

    // Llama a la función para manejar el menú
    WINDOW *menu = menuWin();

    // Espera a la entrada del usuario
    getch();

    // Limpia y cierra ncurses
    delwin(menu);
    endwin();

    return 0;
}