#Makefile como ejemplo con BUE

CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -lm 

all: arbolesBUEADT

arbolesBUEADT: main.c arbolesADT.c barriosADT.c
	$(CC) -c main.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=2 -D ESPECIE=7 -D DIAMETRO=11
	$(CC) -o arbolesBUEADT main.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=2 -D ESPECIE=7 -D DIAMETRO=11






 
	


