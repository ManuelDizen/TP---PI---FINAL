
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "arbolesADT.h"
#include "barriosADT.h"

#define MAX_LEN 2048
#define DECIMAL 2

typedef struct AuxStruct{
    char * nombre;
    double cant_arboles;
} AuxStruct;

double TruncNumber (double num1, int digits);
int sortQ1 (const void * aux1, const void * aux2);
int sortQ2 (const void * aux1,const void * aux2);
int sortQ3 (const void * aux1,const void * aux2);


int main(int argc, char *argv[]) {
    
    if (argc != 3) {
      fprintf(stderr, "Invalid number of arguments\n");
      return 1;
    }
 
    FILE * fileArboles = fopen(argv[1], "r");
    FILE * fileBarrios = fopen(argv[2], "r");
    FILE *q1, *q2, *q3;

    if(fileBarrios == NULL || fileArboles == NULL){
        fprintf(stderr, "Can't open file.\n");
        return 1;
    }

   barriosADT barrios = newBarrios();
    //Leo archivo de barrios
    char line[MAX_LEN];
    fgets(line, MAX_LEN, fileBarrios); //evito la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileBarrios)!=NULL){
        char * token;
        token = strtok (line, ";");
        char * nombre = malloc(strlen(token)+1);
        if (nombre == NULL){
            fprintf(stderr, "There's not enough memory available for allocation");
            return 1;
        }
        strcpy(nombre,token);
        token = strtok (NULL, "\n");
        int habitantes = atoi(token);
        addBarrio(barrios, nombre, habitantes);
    }

    //Leo archivo de arboles
    arbolesADT arboles = newArboles();
    fgets(line, MAX_LEN, fileArboles); //evito leer la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileArboles)!=NULL){
        char * token;
        char * barrio;
        char * nombre;
        int index = 0;
        int diametro;
        for (token = strtok (line, ";"); token != NULL; token = strtok (NULL, ";"))
        {
            if (index == 2){
                barrio = malloc(strlen(token)+1);
                if (barrio == NULL){
                    fprintf(stderr, "There's not enough memory available for allocation");
                    return 1;
                }
                strcpy(barrio, token);
            }
            else if (index == 7){
                nombre = malloc(strlen(token)+1);
                if (nombre == NULL){
                    fprintf(stderr, "There's not enough memory available for allocation");
                    return 1;
                }
                strcpy(nombre, token);
            }
            else if (index == 11){
                diametro = atoi(token);
            }
            index++;
        }
        addArbol(arboles, nombre, diametro);
        incArbolBarrio(barrios, barrio);
     }


    //Abro archivos de query para escribirlos
    q1 = fopen("query1BUE.csv", "wt");
    fprintf(q1, "BARRIO;ARBOLES\n");
    q2 = fopen("query2BUE.csv", "wt");
    fprintf(q2, "BARRIO;ARBOLES_POR_HABITANTE\n");
    q3 = fopen("query3VEC.csv", "wt");
    fprintf(q3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");

    AuxStruct query1[sizeBarrio(barrios)];
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        query1[i].nombre =  nombreBarrio(barrios, i);
        query1[i].cant_arboles = cantArb(barrios, i);
    }
    qsort(query1, sizeBarrio(barrios), sizeof(AuxStruct), sortQ1);
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        fprintf(q1, "%s;%.f\n", query1[i].nombre, query1[i].cant_arboles);
    }

    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        query1[i].nombre = nombreBarrio(barrios, i);
        query1[i].cant_arboles = TruncNumber(promedioArbHab(barrios, i), DECIMAL);
    }

    qsort(query1, sizeBarrio(barrios), sizeof(AuxStruct), sortQ2);
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        fprintf(q2, "%s;%.2f\n", query1[i].nombre, query1[i].cant_arboles);
    }
    
    AuxStruct query3[sizeArboles(arboles)];
    for (size_t i = 0; i < sizeArboles(arboles); i++){
        query3[i].nombre = nombreArbol(arboles, i);
        query3[i].cant_arboles = promedioDiam(arboles, i);
    }
    
    qsort(query3, sizeArboles(arboles), sizeof(AuxStruct), sortQ3);
    for (size_t i = 0; i < sizeArboles(arboles); i++){
        fprintf(q3, "%s;%.2f\n", query3[i].nombre, query3[i].cant_arboles);
    }

    fclose(fileArboles);
    fclose(fileBarrios);
    fclose(q1);
    fclose(q2);
    fclose(q3);
    freeArboles(arboles);
    freeBarrios(barrios);
}

int sortQ1 (const void * aux1, const void * aux2){
    AuxStruct *barrio1 = (AuxStruct *)aux1;
    AuxStruct *barrio2 = (AuxStruct *)aux2;
    int num1 = barrio1->cant_arboles;
    int num2 = barrio2->cant_arboles;
    int comp = num1 - num2;
    if (comp == 0)
        return strcmp(barrio1->nombre, barrio2->nombre);
    if (comp > 0)
        return -1;
    return 1;
}

int sortQ2 (const void * aux1,const void * aux2){
    AuxStruct *barrio1 = (AuxStruct *)aux1;
    AuxStruct *barrio2 = (AuxStruct *)aux2;
    double num1 = TruncNumber(barrio1->cant_arboles, DECIMAL);
    double num2 = TruncNumber(barrio2->cant_arboles, DECIMAL);
    double comp = num1 - num2;
    if (comp == 0)
        return strcmp(barrio1->nombre, barrio2->nombre);
    if (comp > 0)
        return -1;
    return 1;
}

int sortQ3 (const void * aux1,const void * aux2){
    AuxStruct *arbol1 = (AuxStruct *)aux1;
    AuxStruct *arbol2 = (AuxStruct *)aux2;
    double num1 = arbol1->cant_arboles;
    double num2 = arbol2->cant_arboles;
    double comp = num1 - num2;
    if (comp == 0)
        return strcmp(arbol1->nombre, arbol2->nombre);
    if (comp > 0)
        return -1;
    return 1;
}

double TruncNumber (double num1, int digits){
    int potencia = pow(10, digits);
    int numerador = num1*potencia;
    return numerador/(1.0*potencia);
}



