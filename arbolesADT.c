

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

//Agrega el nodoAUbicar a la lista descendentemente por promedio de diametro. Si son iguales (menor a EPSILON ya que redondeamos a 2 decimales), lo agrega alfabéticamente
static TArboles * ubicaPorDiam(TArboles * first, TArboles * nodoAUbicar, int * ok){
  if(first == NULL){
      first = nodoAUbicar;
      first->next = NULL;
      return first;
  }
  double comp1;
    int comp2;
    if((comp1 = first->diametro_promedio - nodoAUbicar->diametro_promedio) < 0 || (comp1 < EPSILON && (comp2  = strcmp(first->nombre, nodoAUbicar->nombre)) > 0) ){
      nodoAUbicar->next = first;
      return nodoAUbicar;
  }
  if(comp1 < EPSILON && comp2 <= 0){
      nodoAUbicar->next = first->next;
      return first;
  }
  *ok = 1; // si ok vale 1, no es la primer llamada
  first->next = ubicaPorDiam(first->next, nodoAUbicar, ok);
  return first;
}

//crea un nuevo nodo
static TArboles * creaNodo (const char * nombre, long int diametro){
    TArboles * aux = malloc(sizeof(TArboles));
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
    aux->cantidad_arboles = 1;
    aux->diametro_promedio = diametro;
    aux->next = NULL;
    return aux;
}

static TArboles * getArbolRec(TArboles * first, const char * nombre, long int diametro){
    if (first->next == NULL){
        TArboles * new = malloc(sizeof(TArboles));
        if(new == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return NULL;
        }
        new = creaNodo(nombre, diametro);
        return new;
    }
    if (strcmp(first->next->nombre, nombre) == 0){
        TArboles * aux = first->next;
        //Fórmula de promedio iterativo
        aux->diametro_promedio += (1/(1+1.0*aux->cantidad_arboles))*(diametro - aux->diametro_promedio);
        first->next = aux->next;
        return aux;
    }
    return getArbolRec(first->next, nombre, diametro);
}

//Encuentra el nodo el cual quiero insertar. Si ya existe, actualiza los parámetros, lo remueve de la lista y lo devuelve. Si no existe, lo crea y lo devuelve
static TArboles * getArbol(TArboles * first, const char * nombre, long int diametro){
    if (first == NULL){
        TArboles * aux = malloc(sizeof(TArboles));
        if(aux == NULL){
          fprintf(stderr, "There's not enough memory available for allocation");
          return NULL;
        }
        aux = creaNodo(nombre, diametro);
        return aux;
    }
    if (first->next == NULL && strcmp(first->nombre, nombre) == 0){
        TArboles * aux = first;
        aux->diametro_promedio += (1/(1+1.0*aux->cantidad_arboles))*(diametro - aux->diametro_promedio);
        first = NULL;
        return aux;
    }
    return getArbolRec(first, nombre, diametro);
}

void addArbol(arbolesADT arboles, const char * comuna, const char * nombre, long int diametro){
    if (arboles != NULL){
        int ok = 0;
        arboles->firstArbol = getArbol(arboles->firstArbol, nombre, diametro);
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

char * nombreArbol (arbolesADT arboles){
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
