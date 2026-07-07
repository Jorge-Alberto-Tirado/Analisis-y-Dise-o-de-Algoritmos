# Archivo Makefile
# Recuerda: la indentacion antes de $(CC) DEBE ser un TAB, no espacios.

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: codifica decodifica

codifica: codifica.c
	$(CC) $(CFLAGS) codifica.c -o codifica

decodifica: decodifica.c
	$(CC) $(CFLAGS) decodifica.c -o decodifica

clean:
	rm -f codifica decodifica