#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbolesADT.h"

#define MAX_LEN 2048

int main(int argc, char *argv[]) {
/*
    if (argc != 3) {
      fprintf(stderr, "Invalid number of arguments\n");
      return 1;
    }
 */

    FILE * fileArboles = fopen("/Users/milu/Downloads/arbolesBUE.csv", "r");
    FILE * fileBarrios = fopen("/Users/milu/Downloads/barriosBUE.csv", "r");
    FILE *q1, *q2, *q3;

    if(fileBarrios == NULL || fileArboles == NULL)
    {
        fprintf(stderr, "Can't open file.\n");
        return 1;
    }

    arbolesADT arboles = newVector();
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
        addBarrio(arboles, nombre, habitantes);
    }

    //Leo archivo de arboles
    fgets(line, MAX_LEN, fileArboles); //evito leer la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileArboles)!=NULL){
        char * token;
        char * comuna;
        char * nombre;
        int index = 0;
        int diametro;
        for (token = strtok (line, ";"); token != NULL; token = strtok (NULL, ";"))
        {
            if (index == 2){
                comuna = malloc(strlen(token)+1);
                if (comuna == NULL){
                    fprintf(stderr, "There's not enough memory available for allocation");
                    return 1;
                }
                strcpy(comuna, token);
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
        addArbol(arboles, comuna, nombre, diametro);
     }

    
    //Abro archivos de query para escribirlos
    q1 = fopen("/Users/milu/Desktop/Facultad/2020 1C/PI/TP Final/query1.csv", "w");
    fprintf(q1, "BARRIO;ARBOLES\n");
    q2 = fopen("/Users/milu/Desktop/Facultad/2020 1C/PI/TP Final/query2.csv", "w");
    fprintf(q2, "BARRIO;ARBOLES_POR_HABITANTE\n");
    q3 = fopen("/Users/milu/Desktop/Facultad/2020 1C/PI/TP Final/query3.csv", "w");
    fprintf(q3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");

    sortCantArb(arboles);
    for (size_t i = 0; i < sizeBarrio(arboles); i++){
        fprintf(q1, "%s;%li\n", nombreBarrio(arboles, i), cantArb(arboles, i));
    }

    sortArbHab(arboles);
    for (size_t i = 0; i < sizeBarrio(arboles); i++){
        fprintf(q2, "%s;%.2f\n", nombreBarrio(arboles, i), promedioArbHab(arboles, i));
    }

    sortDiam(arboles);
    for (size_t i = 0; i < sizeArboles(arboles); i++){
        fprintf(q3, "%s;%.2f\n", nombreArbol(arboles, i), promedioDiam(arboles, i));
    }

    fclose(fileArboles);
    fclose(fileBarrios);
    fclose(q1);
    fclose(q2);
    fclose(q3);
    freeVector(arboles);
}
