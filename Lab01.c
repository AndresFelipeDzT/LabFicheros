/******************************************************
* Fecha 11/11/2025
* Pontificia Universidad Javeriana
* Profesor: J. Corredor, PhD
* Autor: Andres Diaz
* Materia: Sistemas opertivos
* Temas: Laboratorio01 Sistemas de Ficheros
* Descripcion:
*	Realizar un programa en C que lea de teclado el nombre de un directorio y 
*	muestre en pantalla el nombre y el tamaño de los ficheros que contiene.
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
    DIR *d; //Apuntador al directorio
    char nomdir[90], nomfich[90]; //Variables para los directorios
    struct stat datos; //Estructuras para organizar
    struct dirent *direc;

    printf("Introduzca el Nombre de un Directorio: "); //Parametro de entrada que es el del directrio
    fgets(nomdir, sizeof(nomdir), stdin);
    nomdir[strlen(nomdir)-1] = '\0'; /* Eliminamos el \n del Nombre del Fichero */
    //Si nolo encuentra muestra el mensaje de error
    if ((d = opendir(nomdir)) == NULL) {
        printf("El directorio no existe\n");
        return -1;
    }
    //Mientras lea el directorio obtiene sus datos
    while ((direc = readdir(d)) != NULL) {
        strcpy(nomfich, nomdir); //Obtiene el nombre
        strcat(nomfich, "/"); 
        strcat(nomfich, direc->d_name);
        stat(nomfich, &datos); //Obtiene los datos
        if (S_ISREG(datos.st_mode))
            printf("Nombre: %s\t| Tamaño: %ld\n", direc->d_name, datos.st_size);
    } /* Fin del While */
    
    closedir(d); //Lo cierra
    return 0;
}
