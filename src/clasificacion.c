#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "almPreguntas.h"


// Function to sort the questions out by category
void clasificar_Preguntas(Pregunta preguntas[], int numPreguntas, Pregunta ciencia[], int *numCiencia, Pregunta historia[], int *numHistoria, Pregunta entretenimiento[], int *numEntretenimiento) {
    *numCiencia = 0;              
    *numHistoria = 0;             
    *numEntretenimiento = 0;      

    for (int i = 0; i < numPreguntas; i++) {   // Recorre todas las preguntas
        if (strcmp(preguntas[i].categoria, "Ciencia") == 0) {      // Cuando la categoría es Ciencia      
            ciencia[*numCiencia] = preguntas[i];                   // Añade la pregunta al arreglo de Ciencia        
            (*numCiencia)++;                                             
        } else if (strcmp(preguntas[i].categoria, "Historia") == 0) {    
            historia[*numHistoria] = preguntas[i];                       
            (*numHistoria)++;                                            
        } else if (strcmp(preguntas[i].categoria, "Entretenimiento") == 0) { 
            entretenimiento[*numEntretenimiento] = preguntas[i];         
            (*numEntretenimiento)++;                                     
        }
    }
}

int main() {
    // Inicializar el banco de preguntas y el número de preguntas
    Pregunta *banco_Preguntas = NULL;
    int numPreguntas = 0;

    // Preguntas iniciales
    const char opciones1[4][50] = {"H2O", "O2", "CO2", "H2"};
    agregarPregunta(&banco_Preguntas, &numPreguntas, "¿Cuál es la fórmula química del agua?", "Ciencia", opciones1, 0);

    const char opciones2[4][50] = {"Lincoln", "Jefferson", "Washington", "Adams"};
    agregarPregunta(&banco_Preguntas, &numPreguntas, "¿Quién fue el primer presidente de los Estados Unidos?", "Historia", opciones2, 2);

    const char opciones3[4][50] = {"Titanic", "Star Wars", "Avatar", "Avengers"};
    agregarPregunta(&banco_Preguntas, &numPreguntas, "¿Cuál es la película más taquillera de todos los tiempos?", "Entretenimiento", opciones3, 2);

    // Declarar los arreglos para clasificar las preguntas
    Pregunta ciencia[50];
    Pregunta historia[50];
    Pregunta entretenimiento[50];
    int numCiencia = 0, numHistoria = 0, numEntretenimiento = 0;

    // Clasificar las preguntas
    clasificar_Preguntas(banco_Preguntas, numPreguntas, ciencia, &numCiencia, historia, &numHistoria, entretenimiento, &numEntretenimiento);

    // Imprimir los resultados
    printf("Ciencia:\n");
    for (int i = 0; i < numCiencia; i++) {
        printf("%s\n", ciencia[i].pregunta);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, ciencia[i].opciones[j]);
        }
    }

    printf("\nHistoria:\n");
    for (int i = 0; i < numHistoria; i++) {
        printf("%s\n", historia[i].pregunta);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, historia[i].opciones[j]);
        }
    }

    printf("\nEntretenimiento:\n");
    for (int i = 0; i < numEntretenimiento; i++) {
        printf("%s\n", entretenimiento[i].pregunta);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, entretenimiento[i].opciones[j]);
        }
    }

    // Liberar la memoria dinámica utilizada para el banco de preguntas
    free(banco_Preguntas);

    return 0;
}

