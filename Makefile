#Makefile para BUE y VAN

CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -lasan -lm -ldl

all: arbolesBUEADT arbolesVANADT

arbolesBUEADT: mainBUE.c arbolesADT.c barriosADT.c
	$(CC) -c mainBUE.c arbolesADT.c barriosADT.c $(CFLAGS)
	$(CC) -o arbolesBUEADT mainBUE.o arbolesADT.o barriosADT.o 

arbolesVANADT: mainVAN.c arbolesADT.c barriosADT.c
	$(CC) -c mainVAN.c arbolesADT.c barriosADT.c $(CFLAGS)
	$(CC) -o arbolesVANADT mainVAN.o arbolesADT.o barriosADT.o $(CFLAGS)




 
	


