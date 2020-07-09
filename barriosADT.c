

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

static TBarrios * creaNodoBarrio(const char * nombre, long int cant_hab){
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
    return aux;
}

static TBarrios * addBarrioRec(TBarrios * first, const char * nombre, long int cant_arb, int * ok) {
    long int comp, comp2;
    if(first == NULL || (comp = cant_arb - first->cant_arboles) > 0 || (comp < EPSILON && (comp2=strcmp(nombre, first->nombre)) > 0)) {
        TBarrios * aux = creaNodoBarrio(nombre, cant_arb);
        if(aux == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return first;
        }
        aux->next = first;
        *ok = 1;
        return aux;
    }
    if (comp == 0 && comp2 < 0){
        TBarrios * aux2 = creaNodoBarrio(nombre, cant_arb);
        if(aux2 == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return first;
        }
        aux2->next = first->next;
        first->next = aux2;
        *ok = 1;
        return first;
    }
    first->next = addBarrioRec(first->next, nombre, cant_arb, ok);
    return first;
}

void addBarrio(barriosADT barrios, const char * nombre, long int cant_arb){
    int ok = 0;
    if(barrios == NULL){
      return;
    }
    barrios->firstBarrio = addBarrioRec(barrios->firstBarrio, nombre, cant_arb, &ok);
    if (ok)
        barrios->size++;
}

//ESCRIBIR
void incArbolesBarrio (barriosADT barrios, const char * nombre){
    //buscar el barrio, sumarle uno, fijarse si hay que mover el nodo
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

double nextPromedioArbHab(barriosADT barrios){
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
