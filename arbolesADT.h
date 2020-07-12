

#ifndef pruebaarbolesADT_h
#define pruebaarbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

arbolesADT newArboles(void);
void addArbol (arbolesADT arboles, char * nombre, long int diametro);
size_t sizeArboles (arbolesADT arboles);
char * nombreArbol (arbolesADT arboles, size_t index);
double promedioDiam (arbolesADT arboles, size_t index);
void freeArboles(arbolesADT arboles);


#endif /* pruebaarbolesADT_h */
