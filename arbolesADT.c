#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

//Crea un nuevo conjunto de arboles
arbolesADT nuevoArbol(void){
    return calloc(1, sizeof(arbolesCDT));
}

//Libera la memoria utilizada
void freeArboles(arbolesADT arboles){
    for (int i = 0; i < sizeArboles(arboles); i++)
        free(arboles->arboles[i].nombre);
    free(arboles->arboles);
    free(arboles);
}

//Busca el arbol. Si existe, actualiza sus parametros. Si no, lo crea. Retorna 0 si no hubo errores o 1 si no hay memoria suficiente
int addArbol (arbolesADT arboles, char * nombre, long int diametro){
    for (int i = 0; i < arboles->sizeArboles; i++){
        if (strcmp(arboles->arboles[i].nombre, nombre) == 0){
            arboles->arboles[i].cantidad_arboles++;
            arboles->arboles[i].diametro_total += diametro;
            arboles->arboles[i].diametro_promedio = arboles->arboles[i].diametro_total / arboles->arboles[i].cantidad_arboles;
            return 0;
        }
    }
    errno = 0;
    arboles->arboles = realloc(arboles->arboles, (arboles->sizeArboles +1)*sizeof(TArboles));
    //Si no hay memoria suficiente, retorna 1 y deja que el frontend decida si quiere seguir la ejecución o no
    if (errno == ENOMEM){
        return 1;
    }
    arboles->arboles[arboles->sizeArboles].cantidad_arboles = 1;
    arboles->arboles[arboles->sizeArboles].diametro_total = arboles->arboles[arboles->sizeArboles].diametro_promedio = diametro;
    arboles->arboles[arboles->sizeArboles].nombre = malloc(strlen(nombre)+1);
    if (errno == ENOMEM){
        return 1;
    }
    strcpy(arboles->arboles[arboles->sizeArboles].nombre, nombre);
    arboles->sizeArboles++;
    return 0;
}

//Devuelve la cantidad de arboles distintos
size_t sizeArboles (arbolesADT arboles){
    return arboles->sizeArboles;
}

//Devuelve el nombre de el arbol en la posicion index
char * nombreArbol (arbolesADT arboles, size_t index){
    return arboles->arboles[index].nombre;
}

//Devuelve el promedio diametro del arbol ubicado en la posicion index
double promedioDiam (arbolesADT arboles, size_t index){
    return arboles->arboles[index].diametro_promedio;
}

