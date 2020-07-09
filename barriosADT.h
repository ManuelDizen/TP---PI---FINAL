

#ifndef barriosADT_h
#define barriosADT_h

#include <stdio.h>

typedef struct barriosCDT * barriosADT;

barriosADT newBarrioList(void);
size_t sizeBarrio (barriosADT barrios);
void incArbolesBarrio (barriosADT barrios, const char * nombre);
void actualizaHabitantes (barriosADT barrios, const char * nombre, int habitantes);
void toBeginBarrio (barriosADT barrios);
int hasNextBarrio(barriosADT barrios);
char * nextNombreBarrio(barriosADT barrios);
long int nextCantArb(barriosADT barrios);
double nextPromedioArbHab(barriosADT barrios);
void freeBarrios(barriosADT barrios);

//to array
#endif /* barriosADT_h */
