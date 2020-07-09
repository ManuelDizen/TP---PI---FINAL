
#ifndef pruebaarbolesADT_h
#define pruebaarbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

arbolesADT newVector(void);
//Agrega un barrio nuevo a la lista. Si ya existe, no hace nada
void addBarrio (arbolesADT arboles, char * nombre, long int cant_hab);
void addArbol (arbolesADT arboles, char * barrio, char * nombre, long int diametro);

size_t sizeBarrio (arbolesADT arboles);
size_t sizeArboles (arbolesADT arboles);
char * nombreBarrio (arbolesADT arboles, size_t index);
long int cantArb (arbolesADT arboles, size_t index);
double promedioArbHab (arbolesADT arboles, size_t index);
char * nombreArbol (arbolesADT arboles, size_t index);
double promedioDiam (arbolesADT arboles, size_t index);

void freeVector(arbolesADT arboles);

void sortCantArb (arbolesADT arboles);
void sortArbHab (arbolesADT arboles);
void sortDiam (arbolesADT arboles);

#endif /* pruebaarbolesADT_h */
