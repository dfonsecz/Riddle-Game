#include <ncurses.h>
#include <string.h>  // For C-style strings

int main(int argc, char **argv) {
    // Inicializa la pantalla
    // Configura memoria y limpia la pantalla
    initscr();

    // Posicion de la ventana
    int height, width, start_y, start_x;
    height = 20;
    width = 70;
    start_y = 2;
    start_x = 4;

    // Crea una ventana
    WINDOW *win = newwin(height, width, start_y, start_x);
    refresh();

    // Crea bordes alrededor de la ventana
    box(win, 0, 0);
    wrefresh(win);

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

    while (1) {
        for (int i = 0; i < 4; i++) {
            if (i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, 9 + i, 4, "%s", choices[i]);
            wattroff(win, A_REVERSE);
        }
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
            default:
                break;
        }
        if (choice == 10) // Key para input de 'Enter'
            break;
    }
    
    // Retorna el valor int del key del user input
    getch();

    // Libera la memoria y cierra ncurses
    endwin();

    return 0;
}