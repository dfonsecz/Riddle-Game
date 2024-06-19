
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "preguntas"


typedef struct {
    char pregunta;           
    char categoria;           
    char opciones[4];         
    int respuestaCorrecta;        
} Pregunta;

#include <stdio.h>
#include <stdlib.h>

void leer_preguntas(const char *nombre_archivo) {// funcion para abrir y leer el archivo
    FILE *preguntas = fopen(nombre_archivo, "r");// abriendo el archivo en modo lectura
    if (preguntas == NULL) {// verificar si esta nulo
        perror("Error al abrir el archivo");
        return;
    }

    char linea[1024];
    while (fgets(linea, sizeof(linea), preguntas)) {// leemos el archivo
        printf("%s", linea);//imprimimos las preguntas
    }

    fclose(preguntas);//cerramos el archivo
}

int main() {
    const char *preguntas = "preguntas.csv";
    leer_preguntas(preguntas);
    return 0;
}





