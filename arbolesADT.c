

#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EPSILON 0.01


typedef struct TArboles {
    char * nombre;
    long int cantidad_arboles;
    long int diametro_total;
    double diametro_promedio;
    struct TArboles * next;
} TArboles;

typedef struct arbolesCDT{
    TArboles * firstArbol;
    TArboles * currentArbol;
} arbolesCDT;

arbolesADT newArbolList(void){
    return calloc(1, sizeof(arbolesCDT));
}

static TArboles * ubicaPorDiam(TArboles * first, TArboles * nodoAUbicar, int * ok){
  if(first == NULL){
      return nodoAUbicar;
  }
  double comp1 = first->diametro_promedio - nodoAUbicar->diametro_promedio;
  int comp2 = strcmp(first->nombre, nodoAUbicar->nombre);
  if(comp1 < 0 || (comp1 < EPSILON && comp2 < 0) ){
      nodoAUbicar->next = first;
      return nodoAUbicar;
  }
  if(comp1 < EPSILON && comp2 > 0){
      nodoAUbicar->next = first->next;
      first->next = nodoAUbicar;
      return first;
  }
    *ok = 1; // si ok vale 1, no es la primer llamada
    first->next = ubicaPorDiam(first->next, nodoAUbicar, ok);
    return first;
}

static void findSpot (TArboles * first, const char * nombre, long int diametro, TArboles * nodoAUbicar){
  if(first == NULL){
      nodoAUbicar = malloc(sizeof(TArboles));
      if(nodoAUbicar == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return;
      }
      nodoAUbicar->nombre = malloc(strlen(nombre)+1);
      if (nodoAUbicar->nombre == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return;
      }
      strcpy(nodoAUbicar->nombre, nombre);
      nodoAUbicar->diametro_total = nodoAUbicar->diametro_promedio = diametro;
      nodoAUbicar->cantidad_arboles = 1;
      nodoAUbicar->next = NULL;
      return;
  }
  if(strcmp(first->nombre, nombre) == 0){
    first->diametro_promedio = ((double)(first->diametro_total += diametro) / (double)(++first->cantidad_arboles));
    nodoAUbicar = first;
    first = first->next;
  }
  else
    findSpot(first->next, nombre, diametro, nodoAUbicar);
}

void addArbol(arbolesADT arboles, const char * comuna, const char * nombre, long int diametro){
    if (arboles != NULL){
        TArboles * nodoAUbicar = NULL;
        int ok = 0;
        findSpot(arboles->firstArbol, nombre, diametro, nodoAUbicar);
        arboles->firstArbol = ubicaPorDiam(arboles->firstArbol, nodoAUbicar, &ok);
        if (!ok)
            arboles->firstArbol = nodoAUbicar;
    }
}

void toBeginArbol (arbolesADT arboles){
    arboles->currentArbol = arboles->firstArbol;
}

int hasNextArbol(arbolesADT arboles){
    return arboles != NULL && arboles->currentArbol != NULL;
}

char * nextNombreArbol (arbolesADT arboles){
    if (!hasNextArbol(arboles)){
        return NULL;
    }
    char * aux = malloc(strlen(arboles->currentArbol->nombre)+1);
    if(aux == NULL){
      fprintf(stderr, "There's not enough memory available for allocation");
      return NULL;
    }
    strcpy(aux, arboles->currentArbol->nombre);
    return aux;
}

double nextDiametro (arbolesADT arboles){
    if (arboles == NULL || !hasNextArbol(arboles)){
        return 0;
    }
    double aux = arboles->currentArbol->diametro_promedio;
    arboles->currentArbol = arboles->currentArbol->next;
    return aux;
}

static void freeRecArbol(TArboles * first){
    if(first == NULL){
        return;
    }
    free(first->nombre);
    freeRecArbol(first->next);
    free(first);
}

void freeArboles(arbolesADT arboles){
    freeRecArbol(arboles->firstArbol);
    free(arboles);
}
