TP-PI-FINAL

Cornídez, Milagros 61432
De Simone, Franco 61100
Dizenhaus, Manuel 61101

Para generar un archivo ejecutable es necesario tener descargados y en una misma carpeta
  -TPPI.c
  -barriosADT.c 
  -barriosADT.h
  -arbolesADT.c
  -arbolesADT.h
  -Makefile
Si no se encuentra alguno de estos archivos, no será posible la compilación ni la ejecución del programa.

1- Situarse en la terminal en la carpeta en donde se encuentran los archivos previamente listados.

2- Insertar el comando
  $ make
 Este comando compila el programa y crea un archivo ejecutable y los código objeto (.o) de los código fuente (.c) antes listados.
NOTA: El makefile está diseñado para generar 2 archivos ejecutables, uno para Vancouver y otro para Buenos Aires. Si se quisiera utilizar para otra ciudad con un .csv con formato diferente, se debe actualizar el nombre con el que se creará el archivo ejecutable y los -D de BARRIO, ESPECIE y DIAMETRO con el número de columna en donde se encuentran estos datos en el nuevo archivo (siendo la primer columna la número 0).

3- 
  a) Si se desea ejecutar el programa para Buenos Aires, ingresar el comando
       $ ./arbolesBUE (path a arbolesBUE.csv) (path a barriosBUE.csv)
  b) Si se desea ejecutar el programa para Vancouver, ingresar el comando
       $ ./arbolesVAN (path a arbolesVAN.csv) (path a barriosVAN.csv)
       
Esto creará los archivos query1.csv query2.csv query3.csv basados Buenos Aires o Vancouver dependiendo de qué archivo se ejecutó.
IMPORTANTE: Primero se tiene que escribir el archivo a ejecutar, luego el path al archivo .csv con la información de los árboles de la ciudad y luego el path al arhivo .csv con la información de los barrios de la ciudad.
Si no se respeta el orden, el programa no funcionará correctamente. Si se insertan archivos de más o de menos, el programa informará un error.

4- Insertar el comando
  $ make clean
Este comando elimina los código objeto generados en el punto 2. 



