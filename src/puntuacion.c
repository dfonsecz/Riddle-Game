#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

// Función para leer preguntas desde un archivo
int leerPreguntasDesdeArchivo(const char *nombreArchivo, Pregunta preguntas[], int maxPreguntas) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("No se pudo abrir el archivo de preguntas");
        return 0;
    }

    int numPreguntas = 0;
    char linea[512];
    while (fgets(linea, sizeof(linea), archivo) && numPreguntas < maxPreguntas) {
        Pregunta *p = &preguntas[numPreguntas];
        sscanf(linea, "%[^,],\"%255[^\"]\",%49[^,],%49[^,],%49[^,],%49[^,],%d",
               p->categoria, p->pregunta, p->opciones[0], p->opciones[1], p->opciones[2], p->opciones[3], &p->respuestaCorrecta);
        numPreguntas++;
    }

    fclose(archivo);
    return numPreguntas;
}

// Función para seleccionar una pregunta aleatoria
Pregunta *seleccionarPreguntaAleatoria(Pregunta preguntas[], int numPreguntas, char *category) {
    int indicePregunta = rand() % numPreguntas;
    return &preguntas[indicePregunta];
}

// Función para mostrar una pregunta y sus opciones
void mostrarPregunta(WINDOW *win, Pregunta *p) {
    wclear(win);
    box(win, 0, 0);

    mvwprintw(win, 2, 4, "%s", p->pregunta);
    for (int j = 0; j < 4; j++) {
        mvwprintw(win, 4 + j, 4, "%d. %s", j + 1, p->opciones[j]);
    }

    wrefresh(win);
}

// Función para obtener la respuesta del usuario
int obtenerRespuestaUsuario(WINDOW *win) {
    int respuesta = -1;
    char buffer[10];

    echo();
    mvwgetstr(win, 9, 4, buffer);
    noecho();

    if (sscanf(buffer, "%d", &respuesta) == 1 && respuesta >= 1 && respuesta <= 4) {
        return respuesta;
    }
    return -1; // Indica una respuesta inválida
}