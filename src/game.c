#include <ncurses.h>
#include "../include/game.h"

int openGame(WINDOW *win){
    // Realizar operaciones en la ventana del juego
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, 2, 4, "Riddle Game");
    mvwprintw(win, 4, 4, "Puntuación: ");
    mvwprintw(win, 5, 4, "Tiempo restante: ");
    mvwprintw(win, 7, 4, "Pregunta. ");
    wrefresh(win);

    // Más lógica del juego aquí...

    return 0;
}