#include <stdio.h>
#include <time.h>

char* getTime() {
    // Obtener el tiempo actual
    time_t timeNow;
    struct tm * timeInfo;
    static char formattedTime[20];

    time(&timeNow);
    timeInfo = localtime(&timeNow);

    // Formatear la fecha y hora
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d,%H:%M:%S", timeInfo);

    return formattedTime;
}

int match() {
    FILE *file;
    char fileName[] = "partidas";
    char buffer[255];

    file = fopen(fileName, "a");
    if (file == NULL) {
        perror("Error al abrir el file");
        return 1;
    }

    // Añadir enlace a puntuacion.c

    fprintf(file, "%s\n", getTime());

    fclose(file);
}