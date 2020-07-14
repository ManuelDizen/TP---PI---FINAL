#Makefile como ejemplo con BUE

objects = TPPI.o barriosADT.o arbolesADT.o
CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -lm 

all: arbolesBUEADT arbolesVANADT

arbolesBUEADT: TPPI.c arbolesADT.c barriosADT.c
	$(CC) -c TPPI.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=2 -D ESPECIE=7 -D DIAMETRO=11
	$(CC) -o arbolesBUEADT TPPI.o arbolesADT.o barriosADT.o  $(CFLAGS) -D BARRIO=2 -D ESPECIE=7 -D DIAMETRO=11
	
arbolesVANADT: TPPI.c arbolesADT.c barriosADT.c
	$(CC) -c TPPI.c arbolesADT.c barriosADT.c $(CFLAGS) -D BARRIO=12 -D ESPECIE=6 -D DIAMETRO=15
	$(CC) -o arbolesVANADT TPPI.o arbolesADT.o barriosADT.o $(CFLAGS) -D BARRIO=12 -D ESPECIE=6 -D DIAMETRO=15

clean :
	-rm $(objects)  






 
	


