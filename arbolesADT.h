
#ifndef arbolesADT_h
#define arbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

arbolesADT newlist(void);

void addBarrio(arbolesADT arboles, const char * name, long int cant);
void addArbol(arbolesADT arboles, const char * comuna, const char * nombre, long int diametro);

void toBeginBarrio (arbolesADT barrios);
void toBeginArbol (arbolesADT arboles);

int hasNextBarrio(arbolesADT barrios);
int hasNextArbol(arbolesADT arboles);

char * nextNombreBarrio (arbolesADT barrios);
long int nextCantArb (arbolesADT barrios);
float nextCantPromedioArboles(arbolesADT barrios);
char * nombreArbol(arbolesADT barrios);
float nextDiametro (arbolesADT arboles);

void freeAll(arbolesADT arboles);

#endif /* pruebaarbolesADT_h */
