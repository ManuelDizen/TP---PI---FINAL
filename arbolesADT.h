

<<<<<<< HEAD
=======

>>>>>>> Pampero
#ifndef arbolesADT_h
#define arbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

<<<<<<< HEAD
arbolesADT nuevoArbol(void);
void addArbol (arbolesADT arboles, char * nombre, long int diametro);
size_t sizeArboles (arbolesADT arboles);
char * nombreArbol (arbolesADT arboles, size_t index);
double promedioDiam (arbolesADT arboles, size_t index);
=======
/*Crea un nuevo conjunto de arboles*/
arbolesADT nuevoArbol(void);

/*Agrega un arbol al conjunto*/
int addArbol (arbolesADT arboles, char * nombre, long int diametro);

/*Devuelve la cantidad de arboles*/
size_t sizeArboles (arbolesADT arboles);

/*Devuelve el nombre del arbol en la posicion index*/
char * nombreArbol (arbolesADT arboles, size_t index);

/*Devuelve el promedio diametro del arbol en la posicion index*/
double promedioDiam (arbolesADT arboles, size_t index);

/*Libera la memoria reservada por el conjunto de arboles*/
>>>>>>> Pampero
void freeArboles(arbolesADT arboles);


#endif /* arbolesADT_h */
