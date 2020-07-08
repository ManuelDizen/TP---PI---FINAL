
#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TArboles {
    char * nombre;
    long int cantidad_arboles;
    long int diametro_total;
    long int diametro_promedio;
    struct TArboles * next;
} TArboles;

typedef struct TBarrios{
    char * nombre;
    long int cant_arboles;
    long int cant_habitantes;
    long int arbol_habitante_promedio;
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

TBarrios * creaNodoBarrio(const char * name, long int cant){
    TBarrios * aux = malloc(sizeof(struct TBarrios));
    if(aux == NULL){
      free(aux);
      return NULL;
    }
    aux->nombre = malloc(strlen(name));
    if(aux->nombre == NULL){
      free(aux->nombre);
      free(aux);
      return NULL;
    }
    strcpy(aux->nombre, name);
    aux->cant_arboles = cant;
    aux->cant_habitantes = aux->arbol_habitante_promedio = 0;
    return aux;
}

static TBarrios * addBarrioRec(TBarrios * first, const char * name, long int cant) {
    int comp, c;
    if(first == NULL || (comp = cant - first->cant_habitantes) > 0 || (comp == 0 && (c=strcmp(name, first->nombre)) > 0)) {
        TBarrios * aux = creaNodoBarrio(name, cant);
        if(aux == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return first;
        }
        aux->next = first;
        return aux;
    }
    if (comp == 0 && c < 0){
        TBarrios * aux2 = creaNodoBarrio(name, cant);
        if(aux2 == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return first;
        }
        aux2->next = first->next;
        first->next = aux2;
        return aux2;
    }
    first->next = addBarrioRec(first->next, name, cant);
    return first;
}

void addBarrio(arbolesADT arboles, const char * name, long int cant){
    if(arboles == NULL){
      return;
    }
    arboles->firstBarrio = addBarrioRec(arboles->firstBarrio, name, cant);
}

TArboles * creaNodoArbol(const char * nombre, int diametro){
    TArboles * aux = malloc(sizeof(TArboles));
    if(aux == NULL){
      fprintf(stderr, "There's not enough memory available for allocation");
      return NULL;
    }
    aux->nombre = malloc(strlen(nombre));
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

TArboles * ubicaPorDiam(TArboles * first, TArboles * nodoAUbicar){
  if(first == NULL){
    first = nodoAUbicar;
    return first;
  }
  int c;
  if((c = first->diametro_promedio - nodoAUbicar->diametro_promedio) < 0){
    nodoAUbicar->next = first;
    first = first->next;
    return nodoAUbicar;
  }
  if(c == 0){
    int d;
    if((d = strcmp(first->nombre, nodoAUbicar->nombre)) < 0){
      nodoAUbicar->next = first;
      return nodoAUbicar;
    }
    if(d == 0){
      return first;
    }
    nodoAUbicar->next = first->next;
    first->next = nodoAUbicar;
    return first;
  }
  first->next = ubicaPorDiam(first->next, nodoAUbicar);
  return first;
}

TArboles * addArbolRec(TArboles * first, const char * nombre, int diametro, TArboles * nodoAUbicar){
  if(first == NULL){
    first = creaNodoArbol(nombre, diametro);
    nodoAUbicar = first;
    return first;
  }
  int c;
  if((c = strcmp(first->nombre, nombre)) == 0){
    first->diametro_promedio = ((first->diametro_total += diametro) / (first->cantidad_arboles++));
    nodoAUbicar = first;
    return first;
  }
  first->next=addArbolRec(first->next, nombre, diametro, nodoAUbicar);
  return first;
}


static void incArboles (TBarrios * first, char * nombre){
    if (first != NULL){
        if (strcmp(first->nombre, nombre) == 0){
            first->arbol_habitante_promedio = ((first->cant_arboles++) / first->cant_habitantes);
            return;
        }
        incArboles(first->next, nombre);
    }
}

void addArbol(arbolesADT arboles, char * comuna, char * nombre, int diametro){
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

char * nextNombreBarrio (arbolesADT barrios) {
    if ( ! hasNextBarrio(barrios))
        return NULL;
    char * aux = malloc(strlen(barrios->currentBarrio->nombre));
    strcpy(aux, barrios->currentBarrio->nombre);
    barrios->currentBarrio = barrios->currentBarrio->next;
    return aux;
}

long int nextArbBarrio (arbolesADT barrios){
    if ( ! hasNextBarrio(barrios))
        return NULL;
    long int aux = barrios->currentBarrio->cant_arboles;
    barrios->currentBarrio = barrios->currentBarrio->next;
    return aux;
}

long int nextArbHabitante (arbolesADT barrios){
    if ( ! hasNextBarrio(barrios))
        exit(1);
    long int aux = barrios->currentBarrio->arbol_habitante_promedio;
    barrios->currentBarrio = barrios->currentBarrio->next;
    return aux;
}

char * nextNombreArbol (arbolesADT arboles){
    if ( ! hasNextArbol(arboles))
        exit(1);
    char * aux = malloc(strlen(arboles->currentArbol->nombre));
    strcpy(aux, arboles->currentArbol->nombre);
    arboles->currentArbol = arboles->currentArbol->next;
    return aux;
}

long int nextDiametro (arbolesADT arboles){
    if ( ! hasNextArbol(arboles))
        exit(1);
    long int aux = arboles->currentArbol->diametro_promedio;
    arboles->currentArbol = arboles->currentArbol->next;
    return aux;
}
