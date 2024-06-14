#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to store the question
typedef struct {
    char pregunta[256];           
    char categoria[50];           
    char opciones[4][50];         
    int respuestaCorrecta;        
} Pregunta;

void agregarPregunta(Pregunta **banco_Preguntas, int *numPreguntas, const char *pregunta, const char *categoria, const char opciones[4][50], int respuestaCorrecta) {
    *banco_Preguntas = realloc(*banco_Preguntas, (*numPreguntas + 1) * sizeof(Pregunta));

    if (*banco_Preguntas == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(1);
    }

    strncpy((*banco_Preguntas)[*numPreguntas].pregunta, pregunta, sizeof((*banco_Preguntas)[*numPreguntas].pregunta) - 1);
    strncpy((*banco_Preguntas)[*numPreguntas].categoria, categoria, sizeof((*banco_Preguntas)[*numPreguntas].categoria) - 1);
    for (int i = 0; i < 4; i++) {
        strncpy((*banco_Preguntas)[*numPreguntas].opciones[i], opciones[i], sizeof((*banco_Preguntas)[*numPreguntas].opciones[i]) - 1);
    }

    (*banco_Preguntas)[*numPreguntas].respuestaCorrecta = respuestaCorrecta;

    (*numPreguntas)++;
}

void eliminarPreguntas(Pregunta **banco_Preguntas, int *numPreguntas, int indice) {
    if (indice < 0 || indice >= *numPreguntas) {
        printf("Índice inválido\n");
        return;
    }

    for (int i = indice; i < *numPreguntas - 1; i++) {
        (*banco_Preguntas)[i] = (*banco_Preguntas)[i + 1];
    }

    *banco_Preguntas = realloc(*banco_Preguntas, (*numPreguntas - 1) * sizeof(Pregunta));
    if (*banco_Preguntas == NULL && *numPreguntas - 1 > 0) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(1);
    }

    (*numPreguntas)--;
}

void editarPregunta(Pregunta *banco_Preguntas, int numPreguntas) {
    int opcion;
    printf("Seleccione el número de la pregunta que desea editar (0-%d): ", numPreguntas - 1);
    scanf("%d", &opcion);

    if (opcion < 0 || opcion >= numPreguntas) {
        printf("Opción inválida.\n");
        return;
    }

    printf("Edición de la pregunta seleccionada:\n");
    printf("1. Editar pregunta\n");
    printf("2. Editar categoría\n");
    printf("3. Editar opciones\n");
    printf("4. Editar respuesta correcta\n");
    printf("Seleccione la opción que desea editar: ");

    int opcionEditar;
    scanf("%d", &opcionEditar);
    getchar(); // Consumir el salto de línea en el buffer

    switch (opcionEditar) {
        case 1:
            printf("Introduzca la nueva pregunta: ");
            fgets(banco_Preguntas[opcion].pregunta, sizeof(banco_Preguntas[opcion].pregunta), stdin);
            break;
        case 2:
            printf("Introduzca la nueva categoría: ");
            fgets(banco_Preguntas[opcion].categoria, sizeof(banco_Preguntas[opcion].categoria), stdin);
            break;
        case 3:
            printf("Introduzca las nuevas opciones:\n");
            for (int i = 0; i < 4; i++) {
                printf("Opción %d: ", i + 1);
                fgets(banco_Preguntas[opcion].opciones[i], sizeof(banco_Preguntas[opcion].opciones[i]), stdin);
            }
            break;
        case 4:
            printf("Introduzca la nueva respuesta correcta (0-3): ");
            scanf("%d", &banco_Preguntas[opcion].respuestaCorrecta);
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }
}

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
    Pregunta *banco_Preguntas = NULL;
    int numPreguntas = 0;

    char opcion;
    do {
        printf("Menu:\n");
        printf("1. Agregar pregunta\n");
        printf("2. Eliminar pregunta\n");
        printf("3. Editar pregunta\n");
        printf("4. Mostrar preguntas\n");
        printf("5. Clasificar preguntas\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcion);
        getchar(); // Consumir el salto de línea en el buffer

        switch (opcion) {
            case '1': {
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

                printf("Introduzca el número de la respuesta correcta (0-3): ");
                scanf("%d", &respuestaCorrecta);
                getchar(); // Consumir el salto de línea en el buffer

                agregarPregunta(&banco_Preguntas, &numPreguntas, pregunta, categoria, opciones, respuestaCorrecta);
                break;
            }
            case '2': {
                int indice;
                printf("Introduzca el índice de la pregunta a eliminar (0-%d): ", numPreguntas - 1);
                scanf("%d", &indice);
                getchar(); // Consumir el salto de línea en el buffer
                eliminarPreguntas(&banco_Preguntas, &numPreguntas, indice);
                break;
            }
            case '3':
                editarPregunta(banco_Preguntas, numPreguntas);
                break;
            case '4':
                printf("Preguntas:\n");
                for (int i = 0; i < numPreguntas; i++) {
                    printf("Pregunta %d: %s\n", i + 1, banco_Preguntas[i].pregunta);
                    printf("Categoría: %s\n", banco_Preguntas[i].categoria);
                    for (int j = 0; j < 4; j++) {
                        printf("%d. %s\n", j, banco_Preguntas[i].opciones[j]);
                    }
                    printf("Respuesta correcta: %d\n", banco_Preguntas[i].respuestaCorrecta);
                    printf("\n");
                }
                break;
            case '5': {
                Pregunta ciencia[50];
                Pregunta historia[50];
                Pregunta entretenimiento[50];
                int numCiencia = 0, numHistoria = 0, numEntretenimiento = 0;

                clasificar_Preguntas(banco_Preguntas, numPreguntas, ciencia, &numCiencia, historia, &numHistoria, entretenimiento, &numEntretenimiento);

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
            case '6':
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Por favor, intente de nuevo.\n");
                break;
        }
    } while (opcion != '6');

    free(banco_Preguntas);

    return 0;
}

