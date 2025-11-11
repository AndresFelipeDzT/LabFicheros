/******************************************************
* Fecha 11/11/2025
* Pontificia Universidad Javeriana
* Profesor: J. Corredor, PhD
* Autor: Andres Diaz
* Materia: Sistemas opertivos
* Temas: Laboratorio01 Sistemas de Ficheros
* Descripcion:
*    AAAAAAAAAAAAAAAAAAAAAAAAAAAAA
******************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    DIR *d;
    char nomdir[90], nomfich[90];
    struct stat datos;
    struct dirent *direc;

    printf("Introduzca el Nombre de un Directorio: ");
    fgets(nomdir, sizeof(nomdir), stdin);
    nomdir[strlen(nomdir)-1] = '\0'; /* Eliminamos el \n del Nombre del Fichero */
    
    if ((d = opendir(nomdir)) == NULL) {
        printf("El directorio no existe\n");
        return -1;
    }

    while ((direc = readdir(d)) != NULL) {
        strcpy(nomfich, nomdir);
        strcat(nomfich, "/");
        strcat(nomfich, direc->d_name);
        stat(nomfich, &datos);
        if (S_ISREG(datos.st_mode))
            printf("Nombre: %s\t| Tamaño: %ld\n", direc->d_name, datos.st_size);
    } /* Fin del While */
    
    closedir(d);
    return 0;
}
