

#ifndef barriosADT_h
#define barriosADT_h

#include <stdio.h>

typedef struct barriosCDT * barriosADT;

//Estructura auxiliar para pasar a un arreglo sólo los campos que necesito y luego utilizara en qsort
typedef struct TBarrioAux{
    char * nombre;
    double promedioArbHab;
} TBarrioAux;

//Crea una nueva lista
barriosADT newBarrioList(void);

//Agrega un nuevo barrio a la lista, si ya está, no hace nada
void addBarrio(barriosADT barrios, const char * nombre, long int cant_arb);

//Devuelve la cantidad de barrios en la lista
size_t sizeBarrio (barriosADT barrios);

//Incrementa en uno la cantidad de árboles del barrio
void incArbolesBarrio (barriosADT first, const char * nombre);

//Setea el current en first
void toBeginBarrio (barriosADT barrios);

//0 si current es NULL, 1 si no
int hasNextBarrio(barriosADT barrios);

//Devuelve el nombre del barrio del current
char * nombreBarrio(barriosADT barrios);

//Devuelve la cantidad de árboles del current y pasa al siguiente
long int nextCantArb(barriosADT barrios);

//Libera la lista
void freeBarrios(barriosADT barrios);

//Pasa la lista a un arreglo
TBarrioAux * toArray (barriosADT barrios);

#endif /* barriosADT_h */
