#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "arbolesADT.h"
#include "barriosADT.h"

#define MAX_LEN 2048
#define DECIMAL 2
#define BARRIO 2
#define ESPECIE 7
#define DIAMETRO 11

typedef struct AuxStruct{
    char * nombre_auxiliar;
    double valor_auxiliar;
} AuxStruct;

double TruncNumber (double num1, int digits);
int sortCantArboles (const void * aux1, const void * aux2);
int sortPromedioArbHab (const void * aux1,const void * aux2);
int sortPromedioDiamArb (const void * aux1,const void * aux2);


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
        if (fileBarrios == NULL)
            fclose(fileArboles);
        else
            fclose(fileBarrios);
        return 1;
    }

   barriosADT barrios = nuevoBarrio();
    //Leo archivo de barrios
    char line[MAX_LEN];
    fgets(line, MAX_LEN, fileBarrios); //evito la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileBarrios)!=NULL){
        char * token;
        token = strtok (line, ";");
        char * nombre = token;
        token = strtok (NULL, "\n");
        int habitantes = atoi(token);
        addBarrio(barrios, nombre, habitantes);
    }

    //Leo archivo de arboles
    arbolesADT arboles = nuevoArbol();
    fgets(line, MAX_LEN, fileArboles); //evito leer la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileArboles)!=NULL){
        char * token;
        char * barrio;
        char * especie;
        int index = 0;
        int diametro;
        for (token = strtok (line, ";"); token != NULL; token = strtok (NULL, ";"))
        {
            if (index == BARRIO)
                barrio = token;
            else if (index == ESPECIE)
                especie = token;
            else if (index == DIAMETRO)
                diametro = atoi(token);
            index++;
        }
        addArbol(arboles, especie, diametro);
        incArbolBarrio(barrios, barrio);
     }


    //Abro archivos de query para escribirlos
    q1 = fopen("query1.csv", "wt");
    fprintf(q1, "BARRIO;ARBOLES\n");
    q2 = fopen("query2.csv", "wt");
    fprintf(q2, "BARRIO;ARBOLES_POR_HABITANTE\n");
    q3 = fopen("query3.csv", "wt");
    fprintf(q3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");

    AuxStruct cant_arboles[sizeBarrio(barrios)];
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        cant_arboles[i].nombre_auxiliar =  nombreBarrio(barrios, i);
        cant_arboles[i].valor_auxiliar = cantArb(barrios, i);
    }
    qsort(cant_arboles, sizeBarrio(barrios), sizeof(AuxStruct), sortCantArboles);
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        fprintf(q1, "%s;%.f\n", cant_arboles[i].nombre_auxiliar, cant_arboles[i].valor_auxiliar);
    }

    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        cant_arboles[i].nombre_auxiliar = nombreBarrio(barrios, i);
        cant_arboles[i].valor_auxiliar = TruncNumber(promedioArbHab(barrios, i), DECIMAL);
    }

    qsort(cant_arboles, sizeBarrio(barrios), sizeof(AuxStruct), sortPromedioArbHab);
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        fprintf(q2, "%s;%.2f\n", cant_arboles[i].nombre_auxiliar, cant_arboles[i].valor_auxiliar);
    }
    
    AuxStruct diametroArbol[sizeArboles(arboles)];
    for (size_t i = 0; i < sizeArboles(arboles); i++){
        diametroArbol[i].nombre_auxiliar = nombreArbol(arboles, i);
        diametroArbol[i].valor_auxiliar = TruncNumber(promedioDiam(arboles, i), DECIMAL);
    }
    
    qsort(diametroArbol, sizeArboles(arboles), sizeof(AuxStruct), sortPromedioDiamArb);
    for (size_t i = 0; i < sizeArboles(arboles); i++){
        fprintf(q3, "%s;%.2f\n", diametroArbol[i].nombre_auxiliar, diametroArbol[i].valor_auxiliar);
    }

    fclose(fileArboles);
    fclose(fileBarrios);
    fclose(q1);
    fclose(q2);
    fclose(q3);
    freeArboles(arboles);
    freeBarrios(barrios);
    return 0;
}

int sortCantArboles (const void * aux1, const void * aux2){
    AuxStruct *barrio1 = (AuxStruct *)aux1;
    AuxStruct *barrio2 = (AuxStruct *)aux2;
    int num1 = barrio1->valor_auxiliar;
    int num2 = barrio2->valor_auxiliar;
    int comp = num1 - num2;
    int returnValue;
    if (comp == 0)
        returnValue = strcmp(barrio1->nombre_auxiliar, barrio2->nombre_auxiliar);
    else if (comp > 0)
        returnValue = -1;
    else
        returnValue = 1;
    return returnValue;
}

int sortPromedioArbHab (const void * aux1,const void * aux2){
    AuxStruct *barrio1 = (AuxStruct *)aux1;
    AuxStruct *barrio2 = (AuxStruct *)aux2;
    double num1 = barrio1->valor_auxiliar;
    double num2 = barrio2->valor_auxiliar;
    double comp = num1 - num2;
    int returnValue;
    if (comp == 0)
        returnValue = strcmp(barrio1->nombre_auxiliar, barrio2->nombre_auxiliar);
    else if (comp > 0)
        returnValue = -1;
    else
        returnValue = 1;
    return returnValue;
}

int sortPromedioDiamArb (const void * aux1,const void * aux2){
    AuxStruct *arbol1 = (AuxStruct *)aux1;
    AuxStruct *arbol2 = (AuxStruct *)aux2;
    double num1 = arbol1->valor_auxiliar;
    double num2 = arbol2->valor_auxiliar;
    double comp = num1 - num2;
    int returnValue;
    if (comp == 0)
        returnValue = strcmp(arbol1->nombre_auxiliar, arbol2->nombre_auxiliar);
    else if (comp > 0)
        returnValue = -1;
    else
        returnValue = 1;
    return returnValue;
}

double TruncNumber (double num1, int digits){
    int potencia = pow(10, digits);
    int numerador = num1*potencia;
    return numerador/(1.0*potencia);
}



