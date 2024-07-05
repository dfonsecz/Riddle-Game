#include <ncurses.h>
#include <stdio.h>
#include "game.h"

void openGame(WINDOW *win, char *category) {
    // Limpia la ventana y dibuja el marco
    wclear(win);
    box(win, 0, 0);

    // Imprime el encabezado en la ventana
    mvwprintw(win, 2, 4, "Riddle Game");

    // Leer preguntas desde el archivo
    Pregunta preguntas[MAX_PREGUNTAS];
    int numPreguntas = leerPreguntasDesdeArchivo("preguntas.csv", preguntas, MAX_PREGUNTAS);

    // Selecciona una pregunta aleatoria
    Pregunta *pregunta = seleccionarPreguntaAleatoria(preguntas, numPreguntas, category);

    // Muestra la pregunta y las opciones
    mostrarPregunta(win, pregunta);

    wrefresh(win);
}