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


// Función para seleccionar una pregunta aleatoria de una categoría específica
Pregunta *seleccionarPreguntaAleatoria(Pregunta preguntas[], int numPreguntas, const char *categoria) {
    Pregunta *preguntasFiltradas[numPreguntas];
    int numPreguntasFiltradas = 0;

    // Filtrar preguntas por categoría
    for (int i = 0; i < numPreguntas; i++) {
        if (strcmp(preguntas[i].categoria, categoria) == 0 || strcmp(categoria, "Mixto") == 0) {
            preguntasFiltradas[numPreguntasFiltradas] = &preguntas[i];
            numPreguntasFiltradas++;
        }
    }

    if (numPreguntasFiltradas == 0) {
        return NULL; // No hay preguntas en la categoría especificada
    }

    // Seleccionar una pregunta aleatoria de las preguntas filtradas
    int indicePregunta = rand() % numPreguntasFiltradas;
    return preguntasFiltradas[indicePregunta];
}

// Función para mostrar una pregunta y sus opciones
int mostrarPregunta(WINDOW *win, Pregunta *p) {
    wclear(win);
    box(win, 0, 0);

    mvwprintw(win, 3, 4, "%s", p->pregunta);
    for (int j = 0; j < 4; j++) {
        mvwprintw(win, 5 + j, 4, "%d. %s", j + 1, p->opciones[j]);
    }

    wrefresh(win);

    int choice;
    while (1) {
        int ch = wgetch(win);
        if (ch >= '1' && ch <= '4') {
            choice = ch - '0'; // Convertir el carácter a número
            break;
        }
    }

    return choice;
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