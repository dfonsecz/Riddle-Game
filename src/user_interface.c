#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../include/menu.h"

WINDOW *menuWin() {
    // Obtener parámetros de la terminal para centrar la ventana
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Crear una ventana centrada en la terminal
    WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
    refresh();

    // Crear bordes alrededor de la ventana
    box(win, 0, 0);
    wrefresh(win);

    // Definir la barra de menú superior
    Menu menus[3] = {
        {2, "Juego", 'j'},
        {8, "Categoría", 'c'},
        {19, "Ver", 'v'}
    };

    MenuBar menuBar = {
        .win = win,
        .menus = menus,
        .num_menus = 3
    };

    // Definir submenús con diferentes números de opciones
    char *juego_options[] = {"Nuevo juego", "Cargar juego"};
    char *categoria_options[] = {"Ciencia", "Historia", "Entretenimiento", "Mixto"};
    char *ver_options[] = {"Puntuación", "Terminal"};

    SubMenu submenus[3] = {
        {juego_options, 2},
        {categoria_options, 4},
        {ver_options, 2}
    };

    // Imprimir los elementos del menú superior
    for (int i = 0; i < menuBar.num_menus; i++) {
        mvwprintw(menuBar.win, 0, menuBar.menus[i].start_x, "%s", menuBar.menus[i].text);
    }

    // Activar teclado
    keypad(menuBar.win, true);

    int menu_index = 0;
    char *submenu_choice = NULL;
    
    while (1) {
        int choice = wgetch(menuBar.win);

        switch (choice) {
            case 'j':
                menu_index = 0;
                break;
            case 'c':
                menu_index = 1;
                break;
            case 'v':
                menu_index = 2;
                break;
            default:
                break;
        }

        // Actualizar el resaltado del menú
        for (int i = 0; i < menuBar.num_menus; i++) {
            if (i == menu_index)
                wattron(menuBar.win, A_STANDOUT);
            mvwprintw(menuBar.win, 0, menuBar.menus[i].start_x, "%s", menuBar.menus[i].text);
            wattroff(menuBar.win, A_STANDOUT);
        }

        // Si se presiona una tecla de menú, mostrar el submenú
        if (choice == 'j' || choice == 'c' || choice == 'v') {
            submenu_choice = submenuWin(menuBar.win, submenus[menu_index]);

            // Manejar la opción seleccionada del submenú
            if (submenu_choice != NULL) {
                if (strcmp(submenu_choice, "Nuevo juego") == 0) {
                    // Llamar a la función para iniciar un nuevo juego
                    openGame(win);
                }
                else if (strcmp(submenu_choice, "Cargar juego") == 0) {
                    openGame(win);
                }
            }
        }
    }
    // Limpiar y cerrar la ventana del menú principal
    werase(win);
    wrefresh(win);
    delwin(win);

    return menuBar.win;
}

char *submenuWin(WINDOW *parent_win, SubMenu submenu) {
    int num_options = submenu.num_options;

    /// Obtener parámetros de la terminal para centrar la ventana
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // Crear una nueva ventana para el submenú
    WINDOW *submenu_win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
    box(submenu_win, 0, 0);
    wrefresh(submenu_win);

    // Imprimir las opciones del submenú
    for (int i = 0; i < num_options; i++) {
        mvwprintw(submenu_win, i + 1, 1, "%s", submenu.options[i]);
    }
    wrefresh(submenu_win);

    // Activar teclado para el submenú
    keypad(submenu_win, true);

    int highlight = 0;
    int choice;
    char *selected_option = NULL;

    while (1) {
        // Resaltar la opción seleccionada
        for (int i = 0; i < num_options; i++) {
            if (i == highlight)
                wattron(submenu_win, A_STANDOUT);
            mvwprintw(submenu_win, i + 1, 1, "%s", submenu.options[i]);
            wattroff(submenu_win, A_STANDOUT);
        }
        wrefresh(submenu_win);

        choice = wgetch(submenu_win);
        switch (choice) {
            case KEY_UP:
                highlight = (highlight == 0) ? num_options - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == num_options - 1) ? 0 : highlight + 1;
                break;
            case 10:  // Enter key
                // Guardar la opción seleccionada
                selected_option = submenu.options[highlight];
                // Limpiar y cerrar la ventana del submenú
                werase(submenu_win);
                wrefresh(submenu_win);
                delwin(submenu_win);
                return selected_option;
            default:
                break;
        }
    }
}

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