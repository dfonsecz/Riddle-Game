#include <stdio.h>

// almacenar las preguntas con opciones
typedef struct {
    char pregunta[256];
    char opciones[4][50];
    int respuestaCorrecta; // Índice de la respuesta correcta (0-3)
} Pregunta;

// Aquí se manipula la puntuación del jugador
void manejar_Puntuacion(Pregunta preguntas[], int numPreguntas) {
    int puntuacion = 0;
    int fallos = 0;
    int respuesta;

    for (int i = 0; i < numPreguntas; i++) {
        printf("%s\n", preguntas[i].pregunta);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, preguntas[i].opciones[j]);
        }

        printf("Introduce el número de tu respuesta: ");
        scanf("%d", &respuesta);

        if (respuesta - 1 == preguntas[i].respuestaCorrecta) {
            puntuacion += 50;
            printf("Correcto! Puntuación actual: %d\n\n", puntuacion);
        } else {
            fallos++;
            printf("Incorrecto! Has fallado %d veces.\n\n", fallos);
            if (fallos == 3) {
                printf("Has fallado 3 veces. Fin del juego.\n");
                break;
            }
        }
    }

    printf("Puntuación final: %d\n", puntuacion);
}
int main() {
    // Ejemplo de preguntas
    Pregunta banco_Preguntas[] = {
        {"¿Cuál es la fórmula química del agua?", {"H2O", "O2", "CO2", "H2"}, 0},
        {"¿Quién fue el primer presidente de los Estados Unidos?", {"Lincoln", "Jefferson", "Washington", "Adams"}, 2},
        {"¿Cuál es la capital de Francia?", {"Londres", "Madrid", "Berlin", "Paris"}, 3},
        {"¿Cuál es la película más taquillera de todos los tiempos?", {"Titanic", "Star Wars", "Avatar", "Avengers"}, 2},
        };
        
    int numPreguntas = sizeof(banco_Preguntas) / sizeof(banco_Preguntas[0]);

    // Llamar a la función para manejar la puntuación
    manejar_Puntuacion(banco_Preguntas, numPreguntas);

    return 0;
}  
        
