

#ifndef arbolesADT_h
#define arbolesADT_h

#include <stdio.h>

typedef struct arbolesCDT * arbolesADT;

//Sortea los elementos para el 2do query
int compare (const void * aux1,const void * aux2){
    TBarrioAux *barrio1 = (TBarrioAux *)aux1;
    TBarrioAux *barrio2 = (TBarrioAux *)aux2;
    double comp = barrio1->promedioArbHab - barrio2->promedioArbHab;
    if (fabs(comp) < EPSILON)
        return strcmp(barrio1->nombre, barrio2->nombre);
    if (comp > 0)
        return -1;
    return 1;
}

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
