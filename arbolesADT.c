
#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TArboles {
    char * nombre;
    long int cantidad_arboles;
    long int diametro_total;
    double diametro_promedio;
    struct TArboles * next;
} TArboles;

typedef struct TBarrios{
    char * nombre;
    long int cant_arboles;
    long int cant_habitantes;
    double arbol_habitante_promedio;
    struct TBarrios * next;
} TBarrios;

typedef struct arbolesCDT{
    TBarrios * firstBarrio;
    TBarrios * currentBarrio;
    TArboles * firstArbol;
    TArboles * currentArbol;
} arbolesCDT;

arbolesADT newlist(void){
    return calloc(1, sizeof(arbolesCDT));
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

static TBarrios * addBarrioRec(TBarrios * first, const char * nombre, long int cant_hab) {
    long int comp, comp2;
    if(first == NULL || (comp = cant_hab - first->cant_habitantes) > 0 || (comp == 0 && (comp2=strcmp(nombre, first->nombre)) > 0)) {
        TBarrios * aux = creaNodoBarrio(nombre, cant_hab);
        if(aux == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return first;
        }
        aux->next = first;
        return aux;
    }
    if (comp == 0 && comp2 < 0){
        TBarrios * aux2 = creaNodoBarrio(nombre, cant_hab);
        if(aux2 == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return first;
        }
        aux2->next = first->next;
        first->next = aux2;
        return first;
    }
    first->next = addBarrioRec(first->next, nombre, cant_hab);
    return first;
}

void addBarrio(arbolesADT arboles, const char * nombre, long int cant_hab){
    if(arboles == NULL){
      return;
    }
    arboles->firstBarrio = addBarrioRec(arboles->firstBarrio, nombre, cant_hab);
}

static TArboles * creaNodoArbol(const char * nombre, long int diametro){
    TArboles * aux = malloc(sizeof(TArboles));
    if(aux == NULL){
      fprintf(stderr, "There's not enough memory available for allocation");
      return NULL;
    }
    aux->nombre = malloc(strlen(nombre)+1);
    if (aux->nombre == NULL){
        fprintf(stderr, "There's not enough memory available for allocation");
        return NULL;
    }
    strcpy(aux->nombre, nombre);
    aux->diametro_total = aux->diametro_promedio = diametro;
    aux->cantidad_arboles = 1;
    aux->next = NULL;
    return aux;
}

static TArboles * ubicaPorDiam(TArboles * first, TArboles * nodoAUbicar){
  if(first == NULL){
    first = nodoAUbicar;
    return first;
  }
  double comp1 = first->diametro_promedio - nodoAUbicar->diametro_promedio;
  int comp2 = strcmp(first->nombre, nodoAUbicar->nombre));
  if(comp1 < 0 || (comp1 == 0 && comp2 < 0) ){
    nodoAUbicar->next = first;
    first = nodoAUbicar;
    return first;
  }
  if(comp1 == 0){
    if(comp2 > 0){
      nodoAUbicar->next = first->next;
      first->next = nodoAUbicar;
    }
    return first;
  }
  first->next = ubicaPorDiam(first->next, nodoAUbicar);
  return first;
}

static TArboles * addArbolRec(TArboles * first, const char * nombre, long int diametro, TArboles * nodoAUbicar){
  if(first == NULL){
    nodoAUbicar = creaNodoArbol(nombre, diametro);
    return first;
  }
  int comp;
  if((comp = strcmp(first->nombre, nombre)) == 0){
    first->diametro_promedio = ((double)(first->diametro_total += diametro) / (double)(++first->cantidad_arboles));
    nodoAUbicar = first;
    first = first->tail;
    return first;
  }
  first->next=addArbolRec(first->next, nombre, diametro, nodoAUbicar);
  return first;
}


static void incArboles (TBarrios * first, const char * nombre){
    if (first != NULL){
        if (strcmp(first->nombre, nombre) == 0){
            first->arbol_habitante_promedio = ((double)(++first->cant_arboles) / (double)first->cant_habitantes);
            return;
        }
        incArboles(first->next, nombre);
    }
}

void addArbol(arbolesADT arboles, const char * comuna, const char * nombre, long int diametro){
    TArboles * nodoAUbicar = NULL;
    arboles->firstArbol = addArbolRec(arboles->firstArbol, nombre, diametro, nodoAUbicar);
    arboles->firstArbol = ubicaPorDiam(arboles->firstArbol, nodoAUbicar);
    incArboles(arboles->firstBarrio, comuna);
}

void toBeginBarrio (arbolesADT barrios){
    barrios->currentBarrio = barrios->firstBarrio;
}
void toBeginArbol (arbolesADT arboles){
    arboles->currentArbol = arboles->firstArbol;
}

int hasNextBarrio(arbolesADT barrios){
    return barrios->currentBarrio != NULL;
}
int hasNextArbol(arbolesADT arboles){
    return arboles->currentArbol != NULL;
}

char * nextNombreBarrio(arbolesADT barrios){
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

long int nextCantArb(arbolesADT barrios){
  if(barrios == NULL || !hasNextBarrio(barrios)){
    return 0; //sino que retorno?
  }
  long int aux = barrios->currentBarrio->cant_arboles;
  barrios->currentBarrio = barrios->currentBarrio->next;
  return aux;
}

float nextCantPromedioArboles(arbolesADT arboles){
  if(arboles == NULL || !hasNextArbol(arboles)){
    return 0;
  }
  float aux = arboles->currentArbol->arbol_habitante_promedio;
  arboles->currentArbol = arboles->currentArbol->next;
  return aux;
}

char * nombreArbol (arbolesADT arboles){
    if (arboles == NULL ||  !hasNextArbol(arboles)){
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

float nextDiametro (arbolesADT arboles){
    if (arboles == NULL || !hasNextArbol(arboles)){
        return 0;
    }
    float aux = arboles->currentArbol->diametro_promedio;
    arboles->currentArbol = arboles->currentArbol->next;
    return aux;
}

void freeRecArbol(TArboles * first){
  if(first == NULL){
    return;
  }
  freeRecArbol(first->next);
  free(first->nombre);
  free(first);
}

void freeRecBarrio(TBarrios * first){
  if(first == NULL){
    return;
  }
  freeRecBarrio(first->next);
  free(first->nombre)
  free(first);
}

void freeAll(arbolesADT arboles){
  freeRecBarrio(arboles->firstBarrio);
  freeRec(arboles->firstArbol);
  free(arboles);
}
