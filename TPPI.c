#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "arbolesADT.h"
#include "barriosADT.h"

#define MAX_LEN 2048
#define DECIMAL 2

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
    
    /*Se abren ambos csv, arboles y barrios*/
    FILE * fileArboles = fopen(argv[1], "r");
    FILE * fileBarrios = fopen(argv[2], "r");
    FILE *q1, *q2, *q3;

    if(fileBarrios == NULL || fileArboles == NULL){
        if (fileBarrios == NULL){
            fprintf(stderr, "Cannot open %s\n", argv[2]);
            fclose(fileArboles);
        }
        else if (fileArboles == NULL){
            fprintf(stderr, "Cannot open %s\n", argv[1]);
            fclose(fileBarrios);
        }
        return 1;
    }

    barriosADT barrios = nuevoBarrio();
    
    /*Se lee archivo de barrios*/
    char line[MAX_LEN];
    fgets(line, MAX_LEN, fileBarrios); //evito la primer linea de encabezado
    
    /*Hasta que se termine el archivo, se guarda el nombre primero, y la cantidad de habitantes despues,
    agregandolo a la lista, siguiendo el formato del archivo*/
    while(fgets(line, MAX_LEN, fileBarrios)!=NULL){
        char * token;
        token = strtok (line, ";");
        char * barrio = token;
        token = strtok (NULL, "\n");
        int habitantes = atoi(token);
        int ok = addBarrio(barrios, barrio, habitantes);
        if (ok == 1){
            fprintf(stderr, "No hay memoria suficiente para asignar.\n");
            return 1;
        }
        else if (ok == -1)
            fprintf(stderr, "Ya existe el barrio %s.\n", barrio);
    }

    /*Se lee archivo de arboles*/
    arbolesADT arboles = nuevoArbol();
    fgets(line, MAX_LEN, fileArboles); //Se evita leer la primer linea de encabezado
    
    /*Hasta que se termine el archivo, se guardan el barrio, la especie, y el diametro de cada arbol
    siguiendo el formato del archivo*/
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
        int ok = addArbol(arboles, especie, diametro);
        if (ok == 1){
            fprintf(stderr, "No hay memoria suficiente para asignar.\n");
            return 1;
        }
        ok = incArbolBarrio(barrios, barrio);
        if (ok == 1)
            fprintf(stderr, "No se pudo encontrar el barrio %s.\n", barrio);
     }


    /*Se generan los archivos que serán los queries*/
    q1 = fopen("query1.csv", "wt");
    fprintf(q1, "BARRIO;ARBOLES\n");
    q2 = fopen("query2.csv", "wt");
    fprintf(q2, "BARRIO;ARBOLES_POR_HABITANTE\n");
    q3 = fopen("query3.csv", "wt");
    fprintf(q3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");
    
    /*Se copian los barrios a usar a un vector auxiliar de tipo AuxStruct*/
    AuxStruct cant_arboles[sizeBarrio(barrios)];
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        cant_arboles[i].nombre_auxiliar =  nombreBarrio(barrios, i);
        cant_arboles[i].valor_auxiliar = cantArb(barrios, i);
    }
    
    /*Se ordena el vector de acuerdo a la funcion criterio sortCantArboles*/
    qsort(cant_arboles, sizeBarrio(barrios), sizeof(AuxStruct), sortCantArboles);
    
    /*Se copia al query 1 los valores del vector auxiliar ordenado*/
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        fprintf(q1, "%s;%.f\n", cant_arboles[i].nombre_auxiliar, cant_arboles[i].valor_auxiliar);
    }
    
    /*Se reutiliza el vector para el 2do query*/
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        cant_arboles[i].nombre_auxiliar = nombreBarrio(barrios, i);
        cant_arboles[i].valor_auxiliar = TruncNumber(promedioArbHab(barrios, i), DECIMAL);
    }
    
    /*Se ordena el vector de acuerdo a la funcion criterio sortPromedioArbHab*/
    qsort(cant_arboles, sizeBarrio(barrios), sizeof(AuxStruct), sortPromedioArbHab);
    
    /*Se copian los valores del vector auxiliar ordenado al query 2*/
    for (size_t i = 0; i < sizeBarrio(barrios); i++){
        fprintf(q2, "%s;%.2f\n", cant_arboles[i].nombre_auxiliar, cant_arboles[i].valor_auxiliar);
    }
    
    /*Se crea un nuevo vector auxiliar, también de tipo auxStruct*/
    AuxStruct diametroArbol[sizeArboles(arboles)];
    
    /*Se copian los arboles a ordenar a el vector auxiliar*/
    for (size_t i = 0; i < sizeArboles(arboles); i++){
        diametroArbol[i].nombre_auxiliar = nombreArbol(arboles, i);
        diametroArbol[i].valor_auxiliar = TruncNumber(promedioDiam(arboles, i), DECIMAL);
    }
    
    /*Ordena el vector auxiliar diametroArbol de acuerdo a la funcion auxiliar sortPromedioDiamArb*/
    qsort(diametroArbol, sizeArboles(arboles), sizeof(AuxStruct), sortPromedioDiamArb);
    
    /*Copia los valores del vector auxiliar al query 3*/
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
}

/*Devuelve el elemento que tenga mayor cantidad
de arboles, o si son iguales, el menor alfabeticamente*/
int sortCantArboles (const void * aux1, const void * aux2){
    AuxStruct *barrio1 = (AuxStruct *)aux1;
    AuxStruct *barrio2 = (AuxStruct *)aux2;
    int num1 = barrio1->valor_auxiliar;
    int num2 = barrio2->valor_auxiliar;
    int comp = num1 - num2;
    if (comp == 0)
        return strcmp(barrio1->nombre_auxiliar, barrio2->nombre_auxiliar);
    if (comp > 0)
        return -1;
    return 1;
}

/*Devuelve el elemento que tenga mayor promedio de arboles por habitante,
o si son iguales, el menor alfabeticamente*/
int sortPromedioArbHab (const void * aux1,const void * aux2){
    AuxStruct *barrio1 = (AuxStruct *)aux1;
    AuxStruct *barrio2 = (AuxStruct *)aux2;
    double num1 = barrio1->valor_auxiliar;
    double num2 = barrio2->valor_auxiliar;
    double comp = num1 - num2;
    if (comp == 0)
        return strcmp(barrio1->nombre_auxiliar, barrio2->nombre_auxiliar);
    if (comp > 0)
        return -1;
    return 1;
}
/*Devuelve el elemento con mayor diametro promedio, o si son iguales, 
el menor alfabeticamente*/
int sortPromedioDiamArb (const void * aux1,const void * aux2){
    AuxStruct *arbol1 = (AuxStruct *)aux1;
    AuxStruct *arbol2 = (AuxStruct *)aux2;
    double num1 = arbol1->valor_auxiliar;
    double num2 = arbol2->valor_auxiliar;
    double comp = num1 - num2;
    if (comp == 0)
        return strcmp(arbol1->nombre_auxiliar, arbol2->nombre_auxiliar);
    if (comp > 0)
        return -1;
    return 1;
}
/*Trunca un numero a digits digitos*/
double TruncNumber (double num1, int digits){
    int potencia = pow(10, digits);
    int numerador = num1*potencia;
    return numerador/(1.0*potencia);
}



