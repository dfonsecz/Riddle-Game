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


