
#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EPSILON 0.01

typedef struct TArboles {
    char * nombre;
    long int cantidad_arboles;
    double diametro_total;
    double diametro_promedio;
} TArboles;

typedef struct arbolesCDT{
    TArboles * arboles;
    size_t sizeArboles;
} arbolesCDT;

arbolesADT newArboles(void){
    return calloc(1, sizeof(arbolesCDT));
}

void freeArboles(arbolesADT arboles){
    for (int i = 0; i < sizeArboles(arboles); i++)
        free(arboles->arboles[i].nombre);
    free(arboles->arboles);
    free(arboles);
}

void addArbol (arbolesADT arboles, char * nombre, long int diametro){
    for (int i = 0; i < arboles->sizeArboles; i++){
        if (strcmp(arboles->arboles[i].nombre, nombre) == 0){
            arboles->arboles[i].cantidad_arboles++;
            arboles->arboles[i].diametro_total += diametro;
            arboles->arboles[i].diametro_promedio = arboles->arboles[i].diametro_total / arboles->arboles[i].cantidad_arboles;
            return;
        }
    }
    arboles->arboles = realloc(arboles->arboles, (arboles->sizeArboles +1)*sizeof(TArboles));
    if (arboles->arboles == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return;
    }
    arboles->arboles[arboles->sizeArboles].cantidad_arboles = 1;
    arboles->arboles[arboles->sizeArboles].diametro_total = arboles->arboles[arboles->sizeArboles].diametro_promedio = diametro;
    arboles->arboles[arboles->sizeArboles].nombre = malloc(strlen(nombre)+1);
    if (arboles->arboles[arboles->sizeArboles].nombre == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return;
    }
    strcpy(arboles->arboles[arboles->sizeArboles].nombre, nombre);
    arboles->sizeArboles++;
}

size_t sizeArboles (arbolesADT arboles){
    return arboles->sizeArboles;
}

char * nombreArbol (arbolesADT arboles, size_t index){
    return arboles->arboles[index].nombre;
}

double promedioDiam (arbolesADT arboles, size_t index){
    return arboles->arboles[index].diametro_promedio;
}
