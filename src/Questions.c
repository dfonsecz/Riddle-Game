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


void agregarNuevaPregunta(const char *nombre_archivo){
     FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    Pregunta Nuevapregunta;

    printf("ingrese la categoria");// pedirle al usuario la categoria
    fgets(Nuevapregunta.categoria, sizeof(Nuevapregunta.categoria), stdin);// leemos la pregunta con fgets desde la entrada estandar, sizeof para especificar el tama;o de liínea de entrada, prevenimos desbordamientos de buffer.
    Nuevapregunta.categoria[strcspn(Nuevapregunta.categoria, "\n")] = '\0'; // Eliminamos el caracter de nueva linea con strcspn

}

int main() {
    const char *nombre_archivo = "preguntas.txt";
     leer_preguntas(nombre_archivo);

     agregarNuevaPregunta(nombre_archivo);
}



