#Makefile para BUE y VAN

CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -lm 

all: arbolesBUEADT arbolesVANADT

arbolesBUEADT: main.c arbolesADT.c barriosADT.c
	$(CC) -c main.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=2 -D ESPECIE=7 -D DIAMETRO=11
	$(CC) -o arbolesBUEADT main.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=2 -D ESPECIE=7 -D DIAMETRO=11

arbolesVANADT: main.c arbolesADT.c barriosADT.c
	$(CC) -c main.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=12 -D ESPECIE=6 -D DIAMETRO=15
	$(CC) -o arbolesVANADT main.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=12 -D ESPECIE=6 -D DIAMETRO=15





 
	


