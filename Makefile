#Makefile para BUE y VAN

CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -fsanitize=address -lm -ldl

all: arbolesBUEADT arbolesVANADT

arbolesBUEADT: mainBUE.c arbolesADT.c barriosADT.c
	$(CC) -o arbolesBUEADT mainBUE.c arbolesADT.c barriosADT.c $(CFLAGS)

arbolesVANADT: mainVAN.c arbolesADT.c barriosADT.c
	$(CC) -o arbolesVANADT mainVAN.c arbolesADT.c barriosADT.c $(CFLAGS)




 
	


