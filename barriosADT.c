

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

static TBarrios * nuevoBarrio(const char * nombre, long int cant_hab){
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
    aux->cant_arboles = 1;
    return aux;
}

static void findBarrio (TBarrios * first, const char * nombre, TBarrios * barrioAUbicar, int * agregar){
    if (first == NULL){
        barrioAUbicar = nuevoBarrio(nombre, 0);
        *agregar = 1;
        return;
    }
    if (strcmp(first->nombre, nombre) == 0){
        first->cant_arboles++;
        barrioAUbicar = first;
        first = first->next;
        return;
    }
    findBarrio(first->next, nombre, barrioAUbicar, agregar);
}

static TBarrios * ubicaBarrio(TBarrios * first, TBarrios * barrioAUbicar, int * ok){
    if(first == NULL){
        first = barrioAUbicar;
        return first;
    }
    long int comp1 = barrioAUbicar->cant_arboles - first->cant_arboles;
    if(comp1 > 0 || (comp1 == 0 && strcmp(barrioAUbicar->nombre, first->nombre) < 0)){
        barrioAUbicar->next = first;
        return barrioAUbicar;
    }
    *ok = 1;
    first->next = ubicaBarrio(first->next, barrioAUbicar, ok);
    return first;
}

static void incBarrio (barriosADT barrios, TBarrios * barrioAUbicar, int agregar){
    if (agregar)
        barrios->size++;
    int ok = 0;
    barrios->firstBarrio = ubicaBarrio(barrios->firstBarrio, barrioAUbicar, &ok);
    if (!ok)
        barrios->firstBarrio = barrioAUbicar;
}

void incArbolesBarrio (barriosADT barrios, const char * nombre){
    TBarrios * barrioAUbicar = NULL;
    int agregar = 0;
    findBarrio(barrios->firstBarrio, nombre, barrioAUbicar, &agregar);
    incBarrio(barrios, barrioAUbicar, agregar);
}

static void actualizaHabitantesRec (TBarrios * first, const char * nombre, int habitantes, TBarrios * barrioAUbicar, int * agregar){
    if (first == NULL){
        barrioAUbicar = nuevoBarrio(nombre, habitantes);
        *agregar = 1;
        return;
    }
    if (strcmp(first->nombre, nombre) == 0){
        first->cant_habitantes = habitantes;
        return;
    }
    actualizaHabitantesRec(first->next, nombre, habitantes, barrioAUbicar, agregar);
}

void actualizaHabitantes (barriosADT barrios, const char * nombre, int habitantes){
    int agregar = 0;
    TBarrios * barrioAUbicar = NULL;
    actualizaHabitantesRec(barrios->firstBarrio, nombre, habitantes, barrioAUbicar, &agregar);
    incBarrio(barrios, barrioAUbicar, agregar);
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
