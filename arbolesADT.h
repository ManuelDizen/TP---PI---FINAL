
#ifndef arbolesADT_h
#define arbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

arbolesADT newlist(void);

void addBarrio(arbolesADT arboles, const char * name, long int cant);
void addArbol(arbolesADT arboles, char * comuna, char * nombre, int diametro);

void toBeginBarrio (arbolesADT barrios);
void toBeginArbol (arbolesADT arboles);

int hasNextBarrio(arbolesADT barrios);
int hasNextArbol(arbolesADT arboles);

char * nextNombreBarrio (arbolesADT barrios);
long int nextCantArb (arbolesADT barrios);
long int nextPromedioArbHab(arbolesADT barrios);
char * nextNombreArbol (arbolesADT arboles);
long int nextDiametro (arbolesADT arboles);

void freeAll(arbolesADT arboles);

#endif /* pruebaarbolesADT_h */
