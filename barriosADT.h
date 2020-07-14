
<<<<<<< HEAD

=======
>>>>>>> Pampero
#ifndef barriosADT_h
#define barriosADT_h

#include <stdio.h>

typedef struct barriosCDT * barriosADT;

<<<<<<< HEAD
barriosADT newBarrios(void);
void addBarrio (barriosADT barrios, char * nombre, long int cant_hab);
void incArbolBarrio(barriosADT barrios, char * nombre);
size_t sizeBarrio (barriosADT barrios);
char * nombreBarrio (barriosADT barrios, size_t index);
long int cantArb (barriosADT barrios, size_t index);
double promedioArbHab (barriosADT barrios, size_t index);
=======
/*Crea un nuevo conjunto de barrios*/
barriosADT nuevoBarrio(void);

/*Agrega un barrio*/
int addBarrio (barriosADT barrios, char * nombre, long int cant_hab);

/*Agrega un arbol al barrio correspondiente*/
int incArbolBarrio(barriosADT barrios, char * nombre);

/*Devuelve la cantidad de barrios*/
size_t sizeBarrio (barriosADT barrios);

/*Devuelve el nombre del barrio*/
char * nombreBarrio (barriosADT barrios, size_t index);

/*Devuelve la cantidad de arboles de un barrio*/
long int cantArb (barriosADT barrios, size_t index);

/*Devuelve la cantidad de arboles que hay por habitante de cierto barrio*/
double promedioArbHab (barriosADT barrios, size_t index);

/*Libera la memoria reservada por el conjunto de barrios*/
>>>>>>> Pampero
void freeBarrios(barriosADT barrios);


#endif /* barriosADT_h */
