
#ifndef pruebaarbolesADT_h
#define pruebaarbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

arbolesADT newlist(void);

void addBarrio(arbolesADT barrios, char * nombre, int habitantes);
void addArbol(arbolesADT arboles, char * comuna, char * nombre, int diametro);

void toBeginBarrio (arbolesADT barrios);
void toBeginArbol (arbolesADT arboles);

int hasNextBarrio(arbolesADT barrios);
int hasNextArbol(arbolesADT arboles);

char * nextNombreBarrio (arbolesADT barrios);
long int nextArbBarrio (arbolesADT barrios);
long int nextArbHabitante (arbolesADT barrios);
char * nextNombreArbol (arbolesADT arboles);
long int nextDiametro (arbolesADT arboles);

void freeAll(arbolesADT arboles);

#endif /* pruebaarbolesADT_h */
