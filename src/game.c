#include <ncurses.h>
#include <stdio.h>
#include "game.h"

void openGame(WINDOW *win, const char *categoria) {
    // Leer preguntas desde el archivo
    Pregunta preguntas[100];
    int numPreguntas = leerPreguntasDesdeArchivo("preguntas.csv", preguntas, 100);

    if (numPreguntas == 0) {
        mvwprintw(win, 2, 4, "No hay preguntas en el archivo.");
        wrefresh(win);
        return;
    }

    int puntuacion = 0;
    int ch;

    while (1) {
        // Seleccionar y mostrar una pregunta aleatoria de la categoría especificada
        Pregunta *pregunta = seleccionarPreguntaAleatoria(preguntas, numPreguntas, categoria);
        if (pregunta != NULL) {
            int respuesta = mostrarPregunta(win, pregunta);

            if (respuesta == pregunta->respuestaCorrecta + 1) {
                puntuacion += 50;
                mvwprintw(win, 10, 4, "Correcto! Puntuacion: %d", puntuacion);
            } else {
                mvwprintw(win, 10, 4, "Incorrecto! Puntuacion: %d", puntuacion);
            }
            mvwprintw(win, 15, 4, "Presiona 'Esc' para ir al menú principal.");
            wrefresh(win);

            ch = wgetch(win);
            if (ch == 27) {
                match(puntuacion);
                break;
            }
            werase(win);  // Limpiar la ventana para la siguiente pregunta
        } else {
            mvwprintw(win, 2, 4, "No hay preguntas en la categoria especificada.");
            wrefresh(win);
            break;
        }
    }
}