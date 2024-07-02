#include <ncurses.h>
#include "../include/menu.h"

int main() {
    initscr();
    noecho();
    cbreak();
    
    // Start the main menu
    menuWin();
    
    // Clean up
    endwin();
    return 0;
}