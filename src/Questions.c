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
void editarPregunta(const char *nombre_archivo){
     FILE *archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }


}
int main() {
    int opcion;
    const char *nombre_archivo = "preguntas.txt";

    printf("opciones\n 1.leer archivo\n 2.agregar pregunta\n ");
    scanf("%d", &opcion);
    while (getchar() != '\n'); // limpiar el búfer de entrada después de leer la opción

    if (opcion == 1) {
        leer_preguntas(nombre_archivo);
    } else if (opcion == 2) {
        agregarNuevaPregunta(nombre_archivo);
    } else {
        printf("opcion invalida\n");
    }

    return 0;
}




