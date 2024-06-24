#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void agregarNuevaPregunta(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    Pregunta Nuevapregunta;

    printf("Ingrese la categoría: ");
    fgets(Nuevapregunta.categoria, sizeof(Nuevapregunta.categoria), stdin);
    Nuevapregunta.categoria[strcspn(Nuevapregunta.categoria, "\n")] = '\0';

    printf("Ingrese la pregunta: ");
    fgets(Nuevapregunta.pregunta, sizeof(Nuevapregunta.pregunta), stdin);
    Nuevapregunta.pregunta[strcspn(Nuevapregunta.pregunta, "\n")] = '\0';

    for (int i = 0; i < 4; i++) {
        printf("Ingrese la opción %d: ", i + 1);
        fgets(Nuevapregunta.opciones[i], sizeof(Nuevapregunta.opciones[i]), stdin);
        Nuevapregunta.opciones[i][strcspn(Nuevapregunta.opciones[i], "\n")] = '\0';
    }

    printf("Ingrese el número de la opción correcta (0-3): ");
    while (scanf("%d", &Nuevapregunta.respuestaCorrecta) != 1 || Nuevapregunta.respuestaCorrecta < 0 || Nuevapregunta.respuestaCorrecta > 3) {
        printf("Entrada inválida. Por favor, ingrese un número entre 0 y 3: ");
        while (getchar() != '\n'); // limpiar el búfer de entrada
    }

    fprintf(archivo, "%s,%s,%s,%s,%s,%s,%d\n",
            Nuevapregunta.categoria,
            Nuevapregunta.pregunta,
            Nuevapregunta.opciones[0],
            Nuevapregunta.opciones[1],
            Nuevapregunta.opciones[2],
            Nuevapregunta.opciones[3],
            Nuevapregunta.respuestaCorrecta);

    fclose(archivo);
}

void editarPregunta(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    Pregunta preguntas[100];
    int count = 0;
    char linea[1024];

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%49[^,],%255[^,],%99[^,],%99[^,],%99[^,],%99[^,],%d",
               preguntas[count].categoria,
               preguntas[count].pregunta,
               preguntas[count].opciones[0],
               preguntas[count].opciones[1],
               preguntas[count].opciones[2],
               preguntas[count].opciones[3],
               &preguntas[count].respuestaCorrecta);
        // Convertir la categoría a minúsculas
        for (int i = 0; preguntas[count].categoria[i]; i++) {
            preguntas[count].categoria[i] = tolower(preguntas[count].categoria[i]);
        }
        count++;
    }

    fclose(archivo);

    Pregunta historia[100], ciencia[100], entretenimiento[100];
    int countHistoria = 0, countCiencia = 0, countEntretenimiento = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(preguntas[i].categoria, "historia") == 0) {
            historia[countHistoria++] = preguntas[i];
        } else if (strcmp(preguntas[i].categoria, "ciencia") == 0) {
            ciencia[countCiencia++] = preguntas[i];
        } else if (strcmp(preguntas[i].categoria, "entretenimiento") == 0) {
            entretenimiento[countEntretenimiento++] = preguntas[i];
        }
    }

    printf("Seleccione la categoría de la pregunta a editar:\n");
    printf("1. Historia\n");
    printf("2. Ciencia\n");
    printf("3. Entretenimiento\n");
    int categoriaOpcion;
    scanf("%d", &categoriaOpcion);
    while (getchar() != '\n'); // limpiar el búfer de entrada

    Pregunta *categoriaSeleccionada;
    int countSeleccionado;

    if (categoriaOpcion == 1) {
        categoriaSeleccionada = historia;
        countSeleccionado = countHistoria;
    } else if (categoriaOpcion == 2) {
        categoriaSeleccionada = ciencia;
        countSeleccionado = countCiencia;
    } else if (categoriaOpcion == 3) {
        categoriaSeleccionada = entretenimiento;
        countSeleccionado = countEntretenimiento;
    } else {
        printf("Opción inválida.\n");
        return;
    }

    printf("Preguntas en la categoría seleccionada:\n");
    for (int i = 0; i < countSeleccionado; i++) {
        printf("%d. %s\n", i + 1, categoriaSeleccionada[i].pregunta);
    }

    printf("Seleccione el número de la pregunta a editar: ");
    int preguntaOpcion;
    scanf("%d", &preguntaOpcion);
    while (getchar() != '\n'); // limpiar el búfer de entrada

    if (preguntaOpcion < 1 || preguntaOpcion > countSeleccionado) {
        printf("Opción inválida.\n");
        return;
    }

    Pregunta *preguntaSeleccionada = &categoriaSeleccionada[preguntaOpcion - 1];

    printf("Seleccione el aspecto a editar:\n");
    printf("1. Categoría\n");
    printf("2. Pregunta\n");
    printf("3. Opciones\n");
    printf("4. Respuesta Correcta\n");
    int aspectoOpcion;
    scanf("%d", &aspectoOpcion);
    while (getchar() != '\n'); // limpiar el búfer de entrada

    if (aspectoOpcion == 1) {
        printf("Ingrese la nueva categoría: ");
        fgets(preguntaSeleccionada->categoria, sizeof(preguntaSeleccionada->categoria), stdin);
        preguntaSeleccionada->categoria[strcspn(preguntaSeleccionada->categoria, "\n")] = '\0';
        // Convertir la nueva categoría a minúsculas
        for (int i = 0; preguntaSeleccionada->categoria[i]; i++) {
            preguntaSeleccionada->categoria[i] = tolower(preguntaSeleccionada->categoria[i]);
        }
    } else if (aspectoOpcion == 2) {
        printf("Ingrese la nueva pregunta: ");
        fgets(preguntaSeleccionada->pregunta, sizeof(preguntaSeleccionada->pregunta), stdin);
        preguntaSeleccionada->pregunta[strcspn(preguntaSeleccionada->pregunta, "\n")] = '\0';
    } else if (aspectoOpcion == 3) {
        for (int i = 0; i < 4; i++) {
            printf("Ingrese la nueva opción %d: ", i + 1);
            fgets(preguntaSeleccionada->opciones[i], sizeof(preguntaSeleccionada->opciones[i]), stdin);
            preguntaSeleccionada->opciones[i][strcspn(preguntaSeleccionada->opciones[i], "\n")] = '\0';
        }
    } else if (aspectoOpcion == 4) {
        printf("Ingrese el nuevo número de la opción correcta (0-3): ");
        while (scanf("%d", &preguntaSeleccionada->respuestaCorrecta) != 1 || preguntaSeleccionada->respuestaCorrecta < 0 || preguntaSeleccionada->respuestaCorrecta > 3) {
            printf("Entrada inválida. Por favor, ingrese un número entre 0 y 3: ");
            while (getchar() != '\n'); // limpiar el búfer de entrada
        }
    } else {
        printf("Opción inválida.\n");
        return;
    }

    archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(archivo, "%s,%s,%s,%s,%s,%s,%d\n",
                preguntas[i].categoria,
                preguntas[i].pregunta,
                preguntas[i].opciones[0],
                preguntas[i].opciones[1],
                preguntas[i].opciones[2],
                preguntas[i].opciones[3],
                preguntas[i].respuestaCorrecta);
    }
    fclose(archivo);
}



int main() {
    int opcion;
    const char *nombre_archivo = "preguntas.txt";

    printf("opciones\n 1.leer archivo\n 2.agregar pregunta\n 3.Editar pregunta\n ");
    scanf("%d", &opcion);
    while (getchar() != '\n'); // limpiar el búfer de entrada después de leer la opción

    if (opcion == 1) {
        leer_preguntas(nombre_archivo);
    } else if (opcion == 2) {
        agregarNuevaPregunta(nombre_archivo);
    } else if(opcion ==3 ){
        editarPregunta(nombre_archivo);
    } 
    else {
        printf("opcion invalida\n");
    } 

    return 0;
}




