
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

barriosADT nuevoBarrio(void){
    return calloc(1, sizeof(barriosCDT));
}

static int findBarrio (TBarrios * barrios, size_t size, char * nombre, int * index){
    for (int i = 0; i < size; i++){
        if (strcmp(barrios[i].nombre, nombre) == 0){
            *index = i;
            return 1;
        }
    }
    return 0;
}

void incArbolBarrio(barriosADT barrios, char * nombre){
    int index;
    if (findBarrio(barrios->barrios, barrios->sizeBarrios, nombre, &index)){
        barrios->barrios[index].cant_arboles++;
        barrios->barrios[index].arbol_habitante_promedio = (double)barrios->barrios[index].cant_arboles / barrios->barrios[index].cant_habitantes;
    }
}

void addBarrio (barriosADT barrios, char * nombre, long int cant_hab){
    int index;
    errno = 0;
    if (!findBarrio(barrios->barrios, barrios->sizeBarrios, nombre, &index)){
        barrios->barrios = realloc(barrios->barrios, (barrios->sizeBarrios +1)*sizeof(TBarrios));
        if (errno == ENOMEM){
            fprintf(stderr, "There's not enough memory available for allocation");
            return;
        }
        barrios->barrios[barrios->sizeBarrios].cant_habitantes = cant_hab;
        barrios->barrios[barrios->sizeBarrios].cant_arboles = barrios->barrios[barrios->sizeBarrios].arbol_habitante_promedio = 0;
        barrios->barrios[barrios->sizeBarrios].nombre = malloc(strlen(nombre)+1);
        if (errno == ENOMEM){
            fprintf(stderr, "There's not enough memory available for allocation");
            return;
        }
        strcpy(barrios->barrios[barrios->sizeBarrios].nombre, nombre);
        barrios->sizeBarrios++;
    }
}

void freeBarrios(barriosADT barrios){
    for (int i = 0; i < sizeBarrio(barrios); i++)
        free(barrios->barrios[i].nombre);
    free(barrios->barrios);
    free(barrios);
}

size_t sizeBarrio (barriosADT barrios){
    return barrios->sizeBarrios;
}

char * nombreBarrio (barriosADT barrios, size_t index){
    return barrios->barrios[index].nombre;
}

long int cantArb (barriosADT barrios, size_t index){
    return barrios->barrios[index].cant_arboles;
}

double promedioArbHab (barriosADT barrios, size_t index){
    return barrios->barrios[index].arbol_habitante_promedio;
}
