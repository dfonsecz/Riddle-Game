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


void agregarPregunta(Pregunta **banco_Preguntas, int *numPreguntas, const char *pregunta, const char *categoria, const char opciones[4][50], int respuestaCorrecta){
 

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


void eliminarPreguntas( Pregunta **banco_Preguntas,int *numPreguntas, int indice){

    if( indice <= 0 || indice >= numPreguntas ){

        printf("indice invalido");
        return; 
    } 

    for (int i = indice; i <= numPreguntas -1 ; i++){

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

