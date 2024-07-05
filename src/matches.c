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

int match(int puntuacion) {
    FILE *file;
    char fileName[] = "partidas.csv";

    // Abrir el archivo en modo append
    file = fopen(fileName, "a");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char puntuacionString[20];
    sprintf(puntuacionString, "%d", puntuacion);

    fprintf(file, "%s,%s\n", getTime(), puntuacionString);

    fclose(file);

    return 0;
}