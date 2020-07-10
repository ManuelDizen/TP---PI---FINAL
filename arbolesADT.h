

#ifndef arbolesADT_h
#define arbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

//Crea una nueva lista
arbolesADT newArbolList(void);

//Añade un árbol a la lista. SI ya está, actualiza los parámetros
void addArbol(arbolesADT arboles, const char * comuna, const char * nombre, long int diametro);

//Setea el current en first
void toBeginArbol (arbolesADT arboles);

//0 si current es nulo, 1 si no
int hasNextArbol(arbolesADT arboles);

//Devuelve el nombre del árbol
char * nombreArbol (arbolesADT arboles);

//Devuelve el diámetro promedio y pasa al siguiente
double nextDiametro (arbolesADT arboles);

//Libera la lista
void freeArboles(arbolesADT arboles);

#endif /* arbolesADT_h */
