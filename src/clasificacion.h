#include <stdio.h>
#include <string.h>

// Structure to store the question
typedef struct {
    char pregunta[256];           
    char categoria[50];           
    char opciones[4][50];         
    int respuestaCorrecta;        
} Pregunta;

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
    //SET OF QUESTIONS
    Pregunta banco_Preguntas[] = {
        {"¿Cuál es la fórmula química del agua?", "Ciencia", {"H2O", "O2", "CO2", "H2"}, 0},
        {"¿Quién fue el primer presidente de los Estados Unidos?", "Historia", {"Lincoln", "Jefferson", "Washington", "Adams"}, 2},
        {"¿Cuál es la película más taquillera de todos los tiempos?", "Entretenimiento", {"Titanic", "Star Wars", "Avatar", "Avengers"}, 2},
        
    };
    int numPreguntas = sizeof(banco_Preguntas) / sizeof(banco_Preguntas[0]); // Calcula el número de preguntas en el banco

    // Array to STORE the classified questions
    Pregunta ciencia[50];          
    Pregunta historia[50];         
    Pregunta entretenimiento[50];  
    int numCiencia, numHistoria, numEntretenimiento; 

    // Clasificar las preguntas
    clasificar_Preguntas(banco_Preguntas, numPreguntas, ciencia, &numCiencia, historia, &numHistoria, entretenimiento, &numEntretenimiento);

    //PRINT RESULTS
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

    return 0;
}