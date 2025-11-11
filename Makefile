############################################################
# Fecha: 11/11/2025
# Pontificia Universidad Javeriana
# Profesor: J. Corredor, PhD
# Autor: Andres Diaz
# Materia: Sistemas Operativos
# Tema: Makefile OpenMP
# Descripción:
#    Archivo que facilita compilar el codigo
############################################################


# Compilador gcc
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Archivos que se van a compilar
SRCS = Lab01.c Lab02.c
# nombres de los ejecutables
EXES = Lab01 Lab02 

# Que los compile todos
all: $(EXES)

# Comando individual para que compile cada uno
Lab01: Lab01.c
	$(CC) $(CFLAGS) -o $@ $<

Lab02: Lab02.c
	$(CC) $(CFLAGS) -o $@ $<
# Limpieza
clean:
	rm -f $(EXES)


