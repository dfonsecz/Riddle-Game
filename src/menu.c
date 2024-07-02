#include <ncurses.h>
#include <string.h>
#include "../include/menu.h"
#include "../include/game.h"

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