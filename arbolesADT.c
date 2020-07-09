
#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TArboles {
    char * nombre;
    long int cantidad_arboles;
    long int diametro_total;
    double diametro_promedio;
} TArboles;

typedef struct TBarrios{
    char * nombre;
    long int cant_arboles;
    long int cant_habitantes;
    double arbol_habitante_promedio;
} TBarrios;

typedef struct arbolesCDT{
    TBarrios * barrios;
    TArboles * arboles;
    size_t sizeBarrios;
    size_t sizeArboles;
} arbolesCDT;

arbolesADT newVector(void){
    return calloc(1, sizeof(arbolesCDT));
}

void freeVector(arbolesADT arboles){
    free(arboles->arboles);
    free(arboles->barrios);
    free(arboles);
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

void addBarrio (arbolesADT arboles, char * nombre, long int cant_hab){
    int index;
    int ok = findBarrio(arboles->barrios, arboles->sizeBarrios, nombre, &index);
    if (ok == 0){
        arboles->barrios = realloc(arboles->barrios, (arboles->sizeBarrios +1)*sizeof(TBarrios));
        if (arboles->barrios == NULL){
            fprintf(stderr, "There's not enough memory available for allocation");
            return;
        }
        arboles->barrios[arboles->sizeBarrios].cant_habitantes = cant_hab;
        arboles->barrios[arboles->sizeBarrios].cant_arboles = arboles->barrios[arboles->sizeBarrios].arbol_habitante_promedio = 0;
        arboles->barrios[arboles->sizeBarrios].nombre = malloc(strlen(nombre)+1);
        if (arboles->barrios[arboles->sizeBarrios].nombre == NULL){
            fprintf(stderr, "There's not enough memory available for allocation");
            return;
        }
        strcpy(arboles->barrios[arboles->sizeBarrios].nombre, nombre);
        arboles->sizeBarrios++;
    }
}

static void incArbolBarrio(TBarrios * barrios, char * nombre, size_t size){
    int index;
    int ok = findBarrio(barrios, size, nombre, &index);
    if (ok){
        barrios[index].cant_arboles++;
        barrios[index].arbol_habitante_promedio = (double)barrios[index].cant_arboles / barrios[index].cant_habitantes;
    }
}

void addArbol (arbolesADT arboles, char * barrio, char * nombre, long int diametro){
    for (int i = 0; i < arboles->sizeArboles; i++){
        if (strcmp(arboles->arboles[i].nombre, nombre) == 0){
            arboles->arboles[i].cantidad_arboles++;
            arboles->arboles[i].diametro_total += diametro;
            arboles->arboles[i].diametro_promedio = (double)arboles->arboles[i].diametro_total / arboles->arboles[i].cantidad_arboles;
            incArbolBarrio(arboles->barrios, barrio, arboles->sizeBarrios);
            return;
        }
    }
    arboles->arboles = realloc(arboles->arboles, (arboles->sizeArboles +1)*sizeof(TArboles));
    if (arboles->arboles == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return;
    }
    arboles->arboles[arboles->sizeArboles].cantidad_arboles = 1;
    arboles->arboles[arboles->sizeArboles].diametro_total = arboles->arboles[arboles->sizeArboles].diametro_promedio = 0;
    arboles->arboles[arboles->sizeArboles].nombre = malloc(strlen(nombre)+1);
    if (arboles->arboles[arboles->sizeArboles].nombre == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return;
    }
    strcpy(arboles->arboles[arboles->sizeArboles].nombre, nombre);
    arboles->sizeArboles++;
    incArbolBarrio(arboles->barrios, barrio, arboles->sizeBarrios);
}

size_t sizeBarrio (arbolesADT arboles){
    return arboles->sizeBarrios;
}

size_t sizeArboles (arbolesADT arboles){
    return arboles->sizeArboles;
}

char * nombreBarrio (arbolesADT arboles, size_t index){
    return arboles->barrios[index].nombre;
}

long int cantArb (arbolesADT arboles, size_t index){
    return arboles->barrios[index].cant_arboles;
}

double promedioArbHab (arbolesADT arboles, size_t index){
    return arboles->barrios[index].arbol_habitante_promedio;
}

char * nombreArbol (arbolesADT arboles, size_t index){
    return arboles->arboles[index].nombre;
}

double promedioDiam (arbolesADT arboles, size_t index){
    return arboles->arboles[index].diametro_promedio;
}

static void swapBarrio (TBarrios * barrios, int index){
    TBarrios aux = barrios[index];
    barrios[index] = barrios[index+1];
    barrios[index+1] = aux;
}

void sortCantArb (arbolesADT arboles){
    int ok = 1;
    for (int j = 0; j < (arboles->sizeBarrios -1); j++){
        ok = 0;
        for (int i = 0; i < (arboles->sizeBarrios - 1 - j); i++){
            long int dif = arboles->barrios[i].cant_arboles - arboles->barrios[i+1].cant_arboles;
            if (dif < 0 || (dif == 0 && strcmp(arboles->barrios[i].nombre, arboles->barrios[i+1].nombre) > 0)){
                swapBarrio(arboles->barrios, i);
                ok = 1;
            }
        }
    }
}

void sortArbHab (arbolesADT arboles){
    int ok = 1;
    for (int j = 0; j < (arboles->sizeBarrios -1); j++){
        ok = 0;
        for (int i = 0; i < (arboles->sizeBarrios - 1 - j); i++){
            double dif = arboles->barrios[i].arbol_habitante_promedio - arboles->barrios[i+1].arbol_habitante_promedio;
            if (dif < 0 || (dif == 0 && strcmp(arboles->barrios[i].nombre, arboles->barrios[i+1].nombre) > 0)){
                swapBarrio(arboles->barrios, i);
                ok = 1;
            }
        }
    }
}

static void swapArbol (TArboles * arboles, int index){
    TArboles aux = arboles[index];
    arboles[index] = arboles[index+1];
    arboles[index+1] = aux;
}

void sortDiam (arbolesADT arboles){
    int ok = 1;
    for (int j = 0; j < (arboles->sizeArboles -1); j++){
        ok = 0;
        for (int i = 0; i < (arboles->sizeArboles - 1 - j); i++){
            double dif = arboles->arboles[i].diametro_promedio - arboles->arboles[i+1].diametro_promedio;
            if (dif < 0 || (dif == 0 && strcmp(arboles->arboles[i].nombre, arboles->arboles[i+1].nombre) > 0)){
                swapArbol(arboles->arboles, i);
                ok = 1;
            }
        }
    }
}
 

