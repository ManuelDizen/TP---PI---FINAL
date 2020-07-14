#include "barriosADT.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>


typedef struct TBarrios{
    char * nombre;
    long int cant_arboles;
    long int cant_habitantes;
    double arbol_habitante_promedio;
} TBarrios;

typedef struct barriosCDT{
    TBarrios * barrios;
    size_t sizeBarrios;
} barriosCDT;

//Crea un nuevo conjunto de barrios
barriosADT nuevoBarrio(void){
    return calloc(1, sizeof(barriosCDT));
}

//Busca el barrio. Devuelve 1 si lo encontro, 0 en caso contrario
static int findBarrio (TBarrios * barrios, size_t size, char * nombre, int * index){
    for (int i = 0; i < size; i++){
        if (strcmp(barrios[i].nombre, nombre) == 0){
            *index = i;
            return 1;
        }
    }
    return 0;
}

//Busca el barrio, si lo encuentra, incrementa la cantidad de arboles, actualiza el diametro promedio y retorna 0. Si no, retorna 1*/
int incArbolBarrio(barriosADT barrios, char * nombre){
    int index;
    if (findBarrio(barrios->barrios, barrios->sizeBarrios, nombre, &index)){
        barrios->barrios[index].cant_arboles++;
        barrios->barrios[index].arbol_habitante_promedio = (double)barrios->barrios[index].cant_arboles / barrios->barrios[index].cant_habitantes;
        return 0;
    }
    return 1;      
}

//Agrega un barrio al vector. Si ya existe, devuelve -1, si no hay memoria sufiente, retorna 1 o si no hay problemas, retorna 0
int addBarrio (barriosADT barrios, char * nombre, long int cant_hab){
    int index;
    errno = 0;
    if (!findBarrio(barrios->barrios, barrios->sizeBarrios, nombre, &index)){
        barrios->barrios = realloc(barrios->barrios, (barrios->sizeBarrios +1)*sizeof(TBarrios));
        if (errno == ENOMEM){
            return 1;
        }
        barrios->barrios[barrios->sizeBarrios].cant_habitantes = cant_hab;
        barrios->barrios[barrios->sizeBarrios].cant_arboles = barrios->barrios[barrios->sizeBarrios].arbol_habitante_promedio = 0;
        barrios->barrios[barrios->sizeBarrios].nombre = malloc(strlen(nombre)+1);
        if (errno == ENOMEM){
            return 1;
        }
        strcpy(barrios->barrios[barrios->sizeBarrios].nombre, nombre);
        barrios->sizeBarrios++;
        return 0;
    }
    return -1;
}

//Libera la memoria utilizada
void freeBarrios(barriosADT barrios){
    for (int i = 0; i < sizeBarrio(barrios); i++)
        free(barrios->barrios[i].nombre);
    free(barrios->barrios);
    free(barrios);
}

//Devuelve la cantidad de barrios
size_t sizeBarrio (barriosADT barrios){
    return barrios->sizeBarrios;
}

//Devuelve el nombre del barrio en la posicion index
char * nombreBarrio (barriosADT barrios, size_t index){
    return barrios->barrios[index].nombre;
}

//Devuelve la cantidad de arboles que hay en el barrio que esta en la posición index
long int cantArb (barriosADT barrios, size_t index){
    return barrios->barrios[index].cant_arboles;
}
//Devuelve el promedio de arboles por habitante del barrio que esta en la posición index
double promedioArbHab (barriosADT barrios, size_t index){
    return barrios->barrios[index].arbol_habitante_promedio;
}
