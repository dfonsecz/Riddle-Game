# include <ncurses.h>

int main(int argc, char ** argv){

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
    WINDOW * win = newwin(height, width, start_y, start_x);
    refresh();

    // Crea bordes alrededor de la ventana
    box(win, 0, 0);
    mvwprintw(win, 2, 4, "Riddle Game\n");
    mvwprintw(win, 4, 4, "Success:\n");
    mvwprintw(win, 5, 4, "timer placeholder\n");
    mvwprintw(win, 7, 4, "QX: Question placeholder\n");
    mvwprintw(win, 9, 4, "A) Option A\n");
    mvwprintw(win, 10, 4, "B) Option B\n");
    mvwprintw(win, 11, 4, "C) Option C\n");
    mvwprintw(win, 12, 4, "D) Option D\n");
    wrefresh(win);

    // Retorna el valor int del key del user input
    getch();
    getch();

    // Libera la memoria y cierra ncurses
    endwin();

    return 0;
}