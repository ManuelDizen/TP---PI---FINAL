

#ifndef barriosADT_h
#define barriosADT_h

#include <stdio.h>

typedef struct TBarrioAux{
    char * nombre;
    double promedioArbHab;
} TBarrioAux;

typedef struct barriosCDT * barriosADT;

barriosADT newBarrioList(void);
void addBarrio(barriosADT barrios, const char * nombre, long int cant_arb);
size_t sizeBarrio (barriosADT barrios);
void incArbolesBarrio (barriosADT first, const char * nombre);
void toBeginBarrio (barriosADT barrios);
int hasNextBarrio(barriosADT barrios);
char * nextNombreBarrio(barriosADT barrios);
long int nextCantArb(barriosADT barrios);
double nextPromedioArbHab(barriosADT barrios);
void freeBarrios(barriosADT barrios);
TBarrioAux * toArray (barriosADT barrios);


#endif /* barriosADT_h */
