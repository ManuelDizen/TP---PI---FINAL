#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "arbolesADT.h"
#include "barriosADT.h"
#define EPSILON 0.01

#define MAX_LEN 2048

int main(int argc, char *argv[]) {

    if (argc != 3) {
      fprintf(stderr, "Invalid number of arguments\n");
      return 1;
    }

    //Abro los archivos.
    FILE * fileArboles = fopen(argv[1], "r");
    FILE * fileBarrios = fopen(argv[2], "r");
    FILE *q1, *q2, *q3;

    if(fileBarrios == NULL || fileArboles == NULL)
    {
        fprintf(stderr, "Can't open file.\n");
        return 1;
    }

    barriosADT barrios = newBarrioList();
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

    arbolesADT arboles = newArbolList();
    fgets(line, MAX_LEN, fileArboles); //evito leer la primer linea de encabezado
    while(fgets(line, MAX_LEN, fileArboles)!=NULL){
        char * token;
        char * comuna;
        char * nombre;
        int index = 0;
        int diametro;
        for (token = strtok (line, ";"); token != NULL; token = strtok (NULL, ";"))
        {
            if (index == 12){
                comuna = malloc(strlen(token)+1);
                if (comuna == NULL){
                    fprintf(stderr, "There's not enough memory available for allocation");
                    return 1;
                }
                strcpy(comuna, token);
            }
            else if (index == 6){
                nombre = malloc(strlen(token)+1);
                if (nombre == NULL){
                    fprintf(stderr, "There's not enough memory available for allocation");
                    return 1;
                }
                strcpy(nombre, token);
            }
            else if (index == 15){
                diametro = atoi(token);
            }
            index++;
        }
        incArbolesBarrio(barrios, comuna);
        addArbol(arboles, comuna, nombre, diametro);
     }

     //Abro archivos de query para escribirlos
     q1 = fopen("query1VAN.csv", "w");
     fprintf(q1, "BARRIO;ARBOLES\n");
     q2 = fopen("query2VAN.csv", "w");
     fprintf(q2, "BARRIO;ARBOLES_POR_HABITANTE\n");
     q3 = fopen("query3VAN.csv", "w");
     fprintf(q3, "NOMBRE_CIENTIFICO;PROMEDIO_DIAMETRO\n");

     //Almaceno en query1VAN.csv
     toBeginBarrio(barrios);
     while (hasNextBarrio(barrios)) {
         fprintf(q1, "%s;%li\n", nombreBarrio(barrios), nextCantArb(barrios));
     }

     //Paso la lista de barrios a un arreglo para poder usar qsort y ordenar la lista en base a cantidad de árboles por habitante
     TBarrioAux * new = toArray(barrios);
     size_t dimArray = sizeBarrio(barrios);
     qsort(new, dimArray, sizeof(TBarrioAux), compare);

     //Almaceno en query2VAN.csv
     for (int i = 0; i < dimArray; i++)
         fprintf(q2, "%s;%.2f\n", new[i].nombre, new[i].promedioArbHab);

     //ALmaceno en query3VAN.csv
     toBeginArbol(arboles);
     printf("%d\n", hasNextArbol(arboles));
     while (hasNextArbol(arboles)) {
         fprintf(q3, "%s;%.2f\n", nombreArbol(arboles), nextDiametro(arboles));
     }

     //Libero la memoria utilizada por ambas listas.
     freeArboles(arboles);
     freeBarrios(barrios);

     //Cierro todos los archivos.
     fclose(fileArboles);
     fclose(fileBarrios);
     fclose(q1);
     fclose(q2);
     fclose(q3);

     return 0;
 }
