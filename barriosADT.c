

#include "barriosADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EPSILON 0.01

typedef struct TBarrios{
    char * nombre;
    long int cant_arboles;
    long int cant_habitantes;
    double arbol_habitante_promedio;
    struct TBarrios * next;
} TBarrios;

typedef struct barriosCDT{
    TBarrios * firstBarrio;
    TBarrios * currentBarrio;
    size_t size;
} barriosCDT;

barriosADT newBarrioList(void){
    return calloc(1, sizeof(barriosCDT));
}

size_t sizeBarrio (barriosADT barrios){
    return barrios->size;
}



static TBarrios * addBarrioRec(TBarrios * first, const char * nombre, long int cant_hab, int * ok) {
    if(first == NULL ||strcmp(first->nombre, nombre) > 0){
        TBarrios * aux = malloc(sizeof(struct TBarrios));
        if(aux == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return NULL;
        }
        aux->nombre = malloc(strlen(nombre)+1);
        if(aux->nombre == NULL){
            fprintf(stderr, "There's not enough memory available for allocation");
            return NULL;
        }
        strcpy(aux->nombre, nombre);
        aux->cant_habitantes = cant_hab;
        aux->cant_arboles = aux->arbol_habitante_promedio = 0;
        aux->next = first;
        *ok = 1;
        return aux;
    }
    if(strcmp(first->nombre, nombre)< 0)
        first->next = addBarrioRec(first->next, nombre, cant_hab, ok);
    return first;
}

void addBarrio(barriosADT barrios, const char * nombre, long int cant_hab){
    if(barrios == NULL){
      return;
    }
    int ok = 0;
    barrios->firstBarrio = addBarrioRec(barrios->firstBarrio, nombre, cant_hab, &ok);
    if (ok)
        barrios->size++;
}

//HAY QUE ESCRIBIRLA
void incArbolesBarrio (barriosADT barrios, const char * nombre){
    //buscarlo, sumarle uno, fijarse si hay que mover el nodo
    if (first != NULL){
        if (strcmp(first->nombre, nombre) == 0){
            first->arbol_habitante_promedio = ((double)(++first->cant_arboles) / (double)first->cant_habitantes);
            return;
        }
        incArbolesBarrio(first->next, nombre);
    }
}

void toBeginBarrio (barriosADT barrios){
    barrios->currentBarrio = barrios->firstBarrio;
}

int hasNextBarrio(barriosADT barrios){
    return barrios != NULL && barrios->currentBarrio != NULL;
}

char * nextNombreBarrio(barriosADT barrios){
    if(barrios == NULL || !hasNextBarrio(barrios)){
        return NULL;
    }
    char * aux = malloc(strlen(barrios->currentBarrio->nombre)+1);
    if(aux == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return NULL;
    }
    strcpy(aux, barrios->currentBarrio->nombre);
    return aux;
}

long int nextCantArb(barriosADT barrios){
    if(!hasNextBarrio(barrios)){
        return -1;
    }
    long int aux = barrios->currentBarrio->cant_arboles;
    barrios->currentBarrio = barrios->currentBarrio->next;
    return aux;
}

double nextCantPromedioArboles(barriosADT barrios){
  if(!hasNextBarrio(barrios)){
    return -1;
  }
  double aux = barrios->currentBarrio->arbol_habitante_promedio;
  barrios->currentBarrio = barrios->currentBarrio->next;
  return aux;
}


static void freeRecBarrio(TBarrios * first){
    if(first == NULL){
        return;
    }
    free(first->nombre);
    freeRecBarrio(first->next);
    free(first->nombre);
    free(first);
}

void freeBarrios(barriosADT barrios){
    freeRecBarrio(barrios->firstBarrio);
    free(barrios);
}

TBarrioAux * toArray (barriosADT barrios){
    TBarrioAux * resp = malloc(barrios->size * sizeof(TBarrioAux));
    if (resp == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return NULL;
    }
    TBarrios * aux = barrios->firstBarrio;
    int i = 0;
    while (aux != NULL){
        resp[i].nombre = malloc(strlen(aux->nombre)+1);
        if (resp[i].nombre == NULL){
            fprintf(stderr, "There's not enough memory available for allocation");
            return NULL;
        }
        strcpy(resp[i].nombre, aux->nombre);
        resp[i].promedioArbHab = aux->arbol_habitante_promedio;
        aux = aux->next;
        i++;
    }
    return resp;
}
