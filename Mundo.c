#include "Mundo.h"
#include "Io.h"
#include "Robot.h"
#include "Manufactura.h"
#include <stdio.h>
#include <stdlib.h>



void crear_mundo(int tamanio){

    /*
    - Funcion que crea el mundo y lo inicializa con las estructuras I y O en la primera y ultima posicion respectivamente.
    - Recibe un entero que representa el tamaño del mundo.
    - No devuelve nada.
    */

   //Asigando memoria para el mundo(arreglo de punteros a casillas)
    mundo = (void **)malloc(tamanio * sizeof(void *));
    if (mundo == NULL)
    {
        printf("No se pudo crear el mundo\n");
        exit(1);
    }

    //Incializando cada casilla del mundo
    for (int i = 0; i < tamanio; i++)
    {
        mundo[i] = (casilla *)malloc(sizeof(casilla));
        if (mundo[i] == NULL){
            printf("No se pudo crear la casilla %d\n", i);
            exit(1);
        }

        //Inicializando cada casilla del mundo
        ((casilla *)mundo[i])->tipo_estructura = ' ';
        ((casilla *)mundo[i])->estructura = NULL;
        ((casilla *)mundo[i])->step = NULL;
    }

    //Inicializando  las dos estructuras I/O del struct io con sus atributos en la primera y ultima posicion del array.

    ((casilla *)mundo[0])->tipo_estructura = 'I';
    ((casilla *)mundo[0])->estructura = (io *)malloc(sizeof(io));
    if (((casilla *)mundo[0])->estructura == NULL){
        printf("No se pudo crear la estructura I\n");
        exit(1);
    }

    //Inicializando el objeto de la estructura I
    ((io *)((casilla *)mundo[0])->estructura)->objeto = (int *)malloc(sizeof(int));
    if (((io *)((casilla *)mundo[0])->estructura)->objeto == NULL){
        printf("No se pudo crear el objeto\n");
        exit(1);
    }
    *((io *)((casilla *)mundo[0])->estructura)->objeto = 1;
    ((io *)((casilla *)mundo[0])->estructura)->entrada_o_salida = 'I';

    ((casilla *)mundo[tamanio - 1])->tipo_estructura = 'O';
    ((casilla *)mundo[tamanio - 1])->estructura = (io *)malloc(sizeof(io));
    if (((casilla *)mundo[tamanio - 1])->estructura == NULL){
        printf("No se pudo crear la estructura O\n");
        exit(1);
    }

    ((io *)((casilla *)mundo[tamanio - 1])->estructura)->objeto = NULL;
    ((io *)((casilla *)mundo[tamanio - 1])->estructura)->entrada_o_salida = 'O';

}


void mostrar_mundo(){

    /*
    - Funcion que recorre el mundo (Arreglo) e imprime por consola el tipo de estructura de cada casilla de forma grafica.
    - No recibe parametros.
    - No devuelve nada.
    */

    //Obteniendo el tamaño del mundo
    int tamano_mundo = 0;
    while (((casilla *)mundo[tamano_mundo])->tipo_estructura != 'O') {
        tamano_mundo++;
    }
    tamano_mundo++;

    printf("");
    for (int i = 0; i<tamano_mundo; i++){
        printf(" -");
    }
    printf("\n");

    for (int i = 0; i<tamano_mundo; i++){
        printf("|");
        if (((casilla *)mundo[i])->tipo_estructura == ' '){
            printf(" ");
        }
        else{
            //Caso impresion de robot
            if (((casilla *)mundo[i])->tipo_estructura == 'R'){
                if (((robot *)((casilla *)mundo[i])->estructura)->direccion == 0){
                    printf("%c<", ((casilla *)mundo[i])->tipo_estructura);
                }
                else{
                    printf("%c>", ((casilla *)mundo[i])->tipo_estructura);
                }
            }else if (((casilla *)mundo[i])->tipo_estructura == 'M'){
                if (((manufactura *)((casilla *)mundo[i])->estructura)->operar == operar_suma)
                    printf("%c+", ((casilla *)mundo[i])->tipo_estructura);
                if (((manufactura *)((casilla *)mundo[i])->estructura)->operar == operar_resta)
                    printf("%c-", ((casilla *)mundo[i])->tipo_estructura);
                if (((manufactura *)((casilla *)mundo[i])->estructura)->operar == operar_multiplicacion)
                    printf("%c*", ((casilla *)mundo[i])->tipo_estructura);
                if (((manufactura *)((casilla *)mundo[i])->estructura)->operar == operar_division)
                    printf("%c/", ((casilla *)mundo[i])->tipo_estructura);

                

            }else{

            printf("%c", ((casilla *)mundo[i])->tipo_estructura);
            }
        }
    }
    printf("|\n");

    for (int i = 0;  i<tamano_mundo; i++)
    {
        printf(" -");
    }
    printf("\n");
    
}


void borrar_mundo(){

    /*
    - Funcion que libera la memoria de cada casilla del mundo y luego libera la memoria del mundo.
    - No recibe parametros.
    - No devuelve nada.
    */

    //Obteniendo el tamaño del mundo
    int tamano_mundo = 0;
    while (((casilla *)mundo[tamano_mundo])->tipo_estructura != 'O') {
        tamano_mundo++;
    }
    tamano_mundo++;

    //liberando memoria de cada casilla
    for (int i = 0; i < tamano_mundo; i++)
    {
        if (((casilla *)mundo[i])->estructura != NULL){
            if (((casilla *)mundo[i])->tipo_estructura == 'R'){
                free(((robot *)((casilla *)mundo[i])->estructura)->inventario);
                free(((robot *)((casilla *)mundo[i])->estructura));
                printf("Robot destruido\n");
            }
            else if (((casilla *)mundo[i])->tipo_estructura == 'M'){
                free(((manufactura *)((casilla *)mundo[i])->estructura));
                printf("Manufactura destruida\n");
            }
            else if (((casilla *)mundo[i])->tipo_estructura == 'I' || ((casilla *)mundo[i])->tipo_estructura == 'O'){
                free(((io *)((casilla *)mundo[i])->estructura)->objeto);
                free(((io *)((casilla *)mundo[i])->estructura));

                printf("I/O destruido\n");
            }
        }
        free(mundo[i]); //liberando memoria de la casilla
        printf("Casilla %d destruida\n", i);
    }

    //liberando memoria del mundo
    free(mundo);
}


void simular(int ticks){

    /*
    - Funcion que simula el el comportamiento de las estructuras en el mundo durante el numero de ticks especificado.
    - Recibe un entero que representa el numero de ticks.
    - No devuelve nada.
    */

    //Obteniendo el tamaño del mundo
    int tamano_mundo = 0;
    while (((casilla *)mundo[tamano_mundo])->tipo_estructura != 'O') {
        tamano_mundo++;
    }
    tamano_mundo++;
    

    int posicion_robot[tamano_mundo];

    for (int i = 0; i < ticks; i++)
    {
        //Caso en que la casilla tenga un robot
        for (int j = 0; j < tamano_mundo; j++)
        {
            //Guardando las posiciones de los robots
            if (((casilla *)mundo[j])->tipo_estructura == 'R'){
                posicion_robot[j] = 1;
            }
            else{
                posicion_robot[j] = 0;
                
            }        
        }

        //Moviendo los robots
        for (int j = 0; j < tamano_mundo; j++)
        {
            if (posicion_robot[j] == 1){
                step_robot(((casilla *)mundo[j])->estructura, j);
            }
        }
    }
    
}

