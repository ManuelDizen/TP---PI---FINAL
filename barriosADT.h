
#ifndef barriosADT_h
#define barriosADT_h

#include <stdio.h>

typedef struct barriosCDT * barriosADT;

//Crea un nuevo conjunto de barrios
barriosADT nuevoBarrio(void);

//Agrega un barrio al vector. Si ya estaba, retorna -1. Si no hay memoria suficente, retorna 1. Si no hay problemas, retorna 0
int addBarrio (barriosADT barrios, char * nombre, long int cant_hab);

//Agrega un arbol al barrio correspondiente. Si no encuentra el barrio retorna 1, caso contrario retorna 0.
int incArbolBarrio(barriosADT barrios, char * nombre);

//Devuelve la cantidad de barrios
size_t sizeBarrio (barriosADT barrios);

//Devuelve el nombre del barrio en la posición index
char * nombreBarrio (barriosADT barrios, size_t index);

//Devuelve la cantidad de arboles del barrio en la posición index
long int cantArb (barriosADT barrios, size_t index);

//Devuelve la cantidad de arboles que hay por habitante en el barrio en la posición index
double promedioArbHab (barriosADT barrios, size_t index);

//Libera la memoria reservada por el conjunto de barrios
void freeBarrios(barriosADT barrios);


#endif /* barriosADT_h */
