
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pruebaarbolesADT.h"

#define MAX_LEN 2048

int main(int argc, char *argv[]) {

    if (argc != 3) {
      fprintf(stderr, "Invalid number of arguments\n");
      return 1;
    }

    FILE * fileArboles = fopen(argv[1], "r");
    FILE * fileBarrios = fopen(argv[2], "r");
    FILE *q1, *q2, *q3;

    if(fileBarrios == NULL || fileArboles == NULL)
    {
        fprintf(stderr, "Can't open file.\n");
        return 1;
    }

    arbolesADT barrios = newlist();
    //Leo archivo de barrios
    char line[MAX_LEN];
    fgets(line, MAX_LEN, fileBarrios); //evito la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileBarrios)!=NULL){
        char * token;
        token = strtok (line, ";");
        char * nombre = malloc(strlen(token));
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
    fgets(line, MAX_LEN, fileArboles); //evito leer la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileArboles)!=NULL){
        char * token, comuna, nombre;
        int index = 0;
        int diametro;
        for (token = strtok (texto, ";"); token != NULL; token = strtok (NULL, ";"))
        {
            if (index == 2){
                comuna = malloc(strlen(token));
                if (comuna == NULL){
                    fprintf(stderr, "There's not enough memory available for allocation");
                    return 1;
                }
                strcpy(comuna, token);
            }
            else if (index == 7){
                nombre = malloc(strlen(token));
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
        addArbol(barrios, comuna, nombre, diametro);
     }

    //Abro archivos de query para escribirlos
    q1 = fopen("query1.csv", "w");
    fprintf(q1, "BARRIO;ARBOLES\n");
    q2 = fopen("query2.csv", "w");
    fprintf(q2, "BARRIO;ARBOLES_POR_HABITANTE\n");
    q3 = fopen("query3.csv", "w");
    fprintf(q3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");


    toBeginBarrio(barrios);
    while ( hasNextBarrio(barrios)) {
        fprintf(q1, "%s;%d\n", nombreBarrio(barrios), nextCantArb(barrios));
    }

    sortByAverage(barrios); //Falta escribir. Para sortear la lista por orden descendente de arb. por habitante

    toBeginBarrio(barrios);
    while(hasNextBarrio(barrios)){
      fprintf(q2, "%s;0.2%f\n", nombreBarrio(barrios), nextCantPromedioArboles(barrios));
    }

    toBeginArbol(barrios);
    while ( hasNextArbol(barrios)) {
        fprintf(q3, "%s;%d\n", nombreArbol(barrios), nextDiametro(barrios));
    }

    fclose(fileArboles);
    fclose(fileBarrios);
    fclose(q1);
    fclose(q2);
    fclose(q3);
}
