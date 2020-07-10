

#ifndef arbolesADT_h
#define arbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

arbolesADT newArbolList(void);
void addArbol(arbolesADT arboles, const char * comuna, const char * nombre, long int diametro);
void toBeginArbol (arbolesADT arboles);
int hasNextArbol(arbolesADT arboles);
char * nextNombreArbol (arbolesADT arboles);
double nextDiametro (arbolesADT arboles);
void freeArboles(arbolesADT arboles);
size_t sizeArbol (arbolesADT arboles);

#endif /* arbolesADT_h */
