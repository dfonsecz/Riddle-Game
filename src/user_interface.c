#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "menu.h"

int main(int argc, char **argv) {
    // Inicializa la pantalla
    // Configura memoria y limpia la pantalla
    initscr();
    noecho();
    curs_set(0);

    // Obtener parámetros de la terminal para centrar ventana
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Crea una ventana centrada en la terminal
    WINDOW *win = newwin(yMax/2, xMax/2, yMax/4, xMax/4);
    refresh();

    // Crea bordes alrededor de la ventana
    box(win, 0, 0);
    wrefresh(win);

    // Barra de menú

    // Definir la barra de menú superior
    Menu menus[3] = {
        {2, "Juego", 'j'},
        {8, "Categoría", 'c'},
        {19, "Ver", 'v'}
    };

    // Imprimir los elementos del menú superior
    int menu_index = 0;
    for (int i = 0; i < 3; i++) {
        mvwprintw(win, 0, menus[i].start_x, "%s", menus[i].text);
    }

    // Mostrar texto en la ventana
    mvwprintw(win, 2, 4, "Riddle Game\n");
    mvwprintw(win, 4, 4, "Success:\n");
    mvwprintw(win, 5, 4, "Placeholder temporizador\n");
    mvwprintw(win, 7, 4, "QX: Placeholder pregunta\n");

    // Activar keypad
    keypad(win, true);

    // Opciones a escoger
    const char *choices[4] = {"Opcion A", "Opcion B", "Opcion C", "Opcion D"};
    int choice;
    int highlight = 0;
    
    // Navegar en el menú y opciones
    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, 9 + i, 4, "%s", choices[i]);
            wattroff(win, A_REVERSE);
        }
        wrefresh(win);

        choice = wgetch(win);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0) highlight = 3;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 3) highlight = 0;
                break;
            case 'j':
                menu_index = 0;
                highlight = 0;
                break;
            case 'c':
                menu_index = 1;
                highlight = 0;
                break;
            case 'v':
                menu_index = 2;
                highlight = 0;
                break;
            default:
                break;
        }
        // Actualizar resaltado de menú
        for (int i = 0; i < 3; i++) {
            if (i == menu_index)
                wattron(win, A_STANDOUT);
            mvwprintw(win, 0, menus[i].start_x, "%s", menus[i].text);
            wattroff(win, A_STANDOUT);
        }

        // Salir del bucle si se presiona 'q' (por ejemplo)
        if (choice == 'q') {
            break;
        }
    }
    
    // Retorna el valor int del key del user input
    getch();

    // Libera la memoria y cierra ncurses
    delwin(win);  // Libera la memoria asignada a la ventana
    endwin();  // Cierra la librería ncurses

    return 0;
}
