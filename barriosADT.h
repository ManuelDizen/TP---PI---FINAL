

#ifndef barriosADT_h
#define barriosADT_h

#include <stdio.h>

typedef struct barriosCDT * barriosADT;

barriosADT newBarrios(void);
void addBarrio (barriosADT barrios, char * nombre, long int cant_hab);
void incArbolBarrio(barriosADT barrios, char * nombre);
size_t sizeBarrio (barriosADT barrios);
char * nombreBarrio (barriosADT barrios, size_t index);
long int cantArb (barriosADT barrios, size_t index);
double promedioArbHab (barriosADT barrios, size_t index);
void freeBarrios(barriosADT barrios);


#endif /* barriosADT_h */
