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

<<<<<<< HEAD
=======
/*Crea un nuevo conjunto de arboles*/
>>>>>>> Pampero
arbolesADT nuevoArbol(void){
    return calloc(1, sizeof(arbolesCDT));
}

<<<<<<< HEAD
=======
/*Libera la memoria utilizada*/
>>>>>>> Pampero
void freeArboles(arbolesADT arboles){
    for (int i = 0; i < sizeArboles(arboles); i++)
        free(arboles->arboles[i].nombre);
    free(arboles->arboles);
    free(arboles);
}

<<<<<<< HEAD
void addArbol (arbolesADT arboles, char * nombre, long int diametro){
=======
/*Busca el arbol. Si existe, actualiza sus parametros. Si no, lo crea*/
int addArbol (arbolesADT arboles, char * nombre, long int diametro){
>>>>>>> Pampero
    for (int i = 0; i < arboles->sizeArboles; i++){
        if (strcmp(arboles->arboles[i].nombre, nombre) == 0){
            arboles->arboles[i].cantidad_arboles++;
            arboles->arboles[i].diametro_total += diametro;
            arboles->arboles[i].diametro_promedio = arboles->arboles[i].diametro_total / arboles->arboles[i].cantidad_arboles;
<<<<<<< HEAD
            return;
=======
            return 0;
>>>>>>> Pampero
        }
    }
    errno = 0;
    arboles->arboles = realloc(arboles->arboles, (arboles->sizeArboles +1)*sizeof(TArboles));
    if (errno == ENOMEM){
<<<<<<< HEAD
        fprintf(stderr, "There's not enough memory available for allocation");
        return;
=======
        return 1;
>>>>>>> Pampero
    }
    arboles->arboles[arboles->sizeArboles].cantidad_arboles = 1;
    arboles->arboles[arboles->sizeArboles].diametro_total = arboles->arboles[arboles->sizeArboles].diametro_promedio = diametro;
    arboles->arboles[arboles->sizeArboles].nombre = malloc(strlen(nombre)+1);
    if (errno == ENOMEM){
<<<<<<< HEAD
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
=======
        return 1;
    }
    strcpy(arboles->arboles[arboles->sizeArboles].nombre, nombre);
    arboles->sizeArboles++;
    return 0;
}

/*Devuelve la cantidad de arboles distintos*/
size_t sizeArboles (arbolesADT arboles){
    return arboles->sizeArboles;
}

/*Devuelve le nombre de el arbol en la posicion index*/
char * nombreArbol (arbolesADT arboles, size_t index){
    return arboles->arboles[index].nombre;
}

/*Devuelve el promedio diametro del arbol ubicado en la posicion index*/
double promedioDiam (arbolesADT arboles, size_t index){
    return arboles->arboles[index].diametro_promedio;
}

>>>>>>> Pampero
