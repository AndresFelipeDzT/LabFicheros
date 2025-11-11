/******************************************************
* Fecha 11/11/2025
* Pontificia Universidad Javeriana
* Profesor: J. Corredor, PhD
* Autor: Andres Diaz
* Materia: Sistemas opertivos
* Temas: Laboratorio02 Sistemas de Ficheros
* Descripcion:
*	Realizar un programa que reciba un nombre de directorio y muestre por 
*	pantalla los nombres de ficheros y directorios
*	que contiene, su modo, si tienen o no permiso de lectura para el propietario, 
*	si son directorios y, para los ficheros modificados en los últimos 10 días, su fecha de acceso
******************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    char nomdir[256], nomfich[512];
    DIR *d;
    struct dirent *rd1;
    struct stat atr;
    time_t fecha;
    int er;

    printf("Nombre directorio: ");
    fgets(nomdir, sizeof(nomdir), stdin);
    nomdir[strlen(nomdir)-1] = '\0'; // Evitar el salto de linea

    fecha = time(NULL); // Asignar la hora a la fecha 

    if ((d = opendir(nomdir)) == NULL) { //Si no logra abrirlo
        printf("No existe ese directorio\n"); //Muestra el mensaje de error
        return -1;
    } else {
        while ((rd1 = readdir(d)) != NULL) {//Mientras siga leyendo
            // Ignore los . y los doble ..
            if (strcmp(rd1->d_name, ".") == 0 || strcmp(rd1->d_name, "..") == 0) continue;
            // Va armando los caminos de los ficheros 
            strcpy(nomfich, nomdir);
            strcat(nomfich, "/");
            strcat(nomfich, rd1->d_name);
            printf("Fichero/directorio: %s\n", nomfich);

            er = stat(nomfich, &atr);
            if (er != 0) continue; // Si no lo logra irse a la siguiente entrada

            printf("Modo: %o\n", atr.st_mode);

            // Verificar que tiene permisos de propietario para escribir
            if (atr.st_mode & S_IRUSR)
                printf("Permiso R para propietario: Sí\n");
            else
                printf("Permiso R para propietario: No\n");

            // Confirma que es un directorio
            if (S_ISDIR(atr.st_mode))
                printf("Es un directorio\n");

            // incluye las fechas de modificacion
            if (S_ISREG(atr.st_mode)) {
                if ((fecha - 10 * 24 * 60 * 60) < atr.st_mtime) {
                    printf("FICHERO: %s, fecha modificación: %s", rd1->d_name, ctime(&atr.st_mtime));
                }
            }

            printf("\n");
        }
        closedir(d);
    }

    return 0;
}
