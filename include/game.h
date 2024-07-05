#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

#define MAX_PREGUNTAS 100

// Estructura para almacenar preguntas
typedef struct {
    char categoria[50];
    char pregunta[256];
    char opciones[4][50];
    int respuestaCorrecta; // Índice correcto
} Pregunta;

int leerPreguntasDesdeArchivo(const char *nombreArchivo, Pregunta preguntas[], int maxPreguntas);
Pregunta *seleccionarPreguntaAleatoria(Pregunta preguntas[], int numPreguntas, const char *categoria);
Pregunta *seleccionarPreguntaAleatoriaPorCategoria(Pregunta preguntas[], int numPreguntas, const char *categoria);
int mostrarPregunta(WINDOW *win, Pregunta *p);
void openGame(WINDOW *win, const char *category);

#endif