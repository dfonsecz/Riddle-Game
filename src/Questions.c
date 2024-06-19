#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pregunta[256];
    char categoria[50];
    char opciones[4][100];
    int respuestaCorrecta;
} Pregunta;

void leer_preguntas(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }

    fclose(archivo);
}


int main() {
    const char *nombre_archivo = "preguntas.txt";
     leer_preguntas(nombre_archivo);
}



