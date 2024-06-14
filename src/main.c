#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"


void imprimirPreguntas(Pregunta *banco_Preguntas, int numPreguntas) {
    for (int i = 0; i < numPreguntas; i++) {
        printf("Pregunta %d: %s\n", i + 1, banco_Preguntas[i].pregunta);
        printf("Categoría: %s\n", banco_Preguntas[i].categoria);
        for (int j = 0; j < 4; j++) {
            printf("%d. %s\n", j + 1, banco_Preguntas[i].opciones[j]);
        }
        printf("Respuesta correcta: %d\n", banco_Preguntas[i].respuestaCorrecta + 1);
        printf("\n");
    }
}

void menu(Pregunta **banco_Preguntas, int *numPreguntas) {
    int opcion;
    do {
        printf("Menu:\n");
        printf("1. Agregar pregunta\n");
        printf("2. Eliminar pregunta\n");
        printf("3. Editar pregunta\n");
        printf("4. Mostrar preguntas\n");
        printf("5. Clasificar preguntas\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Consumir el salto de línea en el buffer

        switch (opcion) {
            case 1: {
                char pregunta[256];
                char categoria[50];
                char opciones[4][50];
                int respuestaCorrecta;

                printf("Introduzca la pregunta: ");
                fgets(pregunta, sizeof(pregunta), stdin);
                strtok(pregunta, "\n"); // Eliminar el salto de línea final

                printf("Introduzca la categoría: ");
                fgets(categoria, sizeof(categoria), stdin);
                strtok(categoria, "\n"); // Eliminar el salto de línea final

                for (int i = 0; i < 4; i++) {
                    printf("Introduzca la opción %d: ", i + 1);
                    fgets(opciones[i], sizeof(opciones[i]), stdin);
                    strtok(opciones[i], "\n"); // Eliminar el salto de línea final
                }

                printf("Introduzca el número de la respuesta correcta (1-4): ");
                scanf("%d", &respuestaCorrecta);
                getchar(); // Consumir el salto de línea en el buffer

                agregarPregunta(banco_Preguntas, numPreguntas, pregunta, categoria, opciones, respuestaCorrecta - 1);
                break;
            }
            case 2: {
                int indice;
                printf("Introduzca el índice de la pregunta a eliminar (0-%d): ", *numPreguntas - 1);
                scanf("%d", &indice);
                eliminarPreguntas(banco_Preguntas, numPreguntas, indice);
                break;
            }
            case 3:
                editarPregunta(*banco_Preguntas, *numPreguntas);
                break;
            case 4:
                imprimirPreguntas(*banco_Preguntas, *numPreguntas);
                break;
            case 5: {
                Pregunta ciencia[50];
                Pregunta historia[50];
                Pregunta entretenimiento[50];
                int numCiencia = 0, numHistoria = 0, numEntretenimiento = 0;

                clasificar_Preguntas(*banco_Preguntas, *numPreguntas, ciencia, &numCiencia, historia, &numHistoria, entretenimiento, &numEntretenimiento);

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
                break;
            }
            case 6:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Por favor, intente de nuevo.\n");
                break;
        }
    } while (opcion != 6);
}

int main() {
    Pregunta *banco_Preguntas = NULL;
    int numPreguntas = 0;

    menu(&banco_Preguntas, &numPreguntas);

    free(banco_Preguntas);

    return 0;
}
