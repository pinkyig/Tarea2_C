#include "Manufactura.h"
#include "Robot.h"
#include "Io.h"
#include "Mundo.h"
#include <stdio.h>
#include <stdlib.h>





manufactura * crear_manufactura(){
    /*
    - Funcion que crea una manufactura y la inicializ todas sus variables y/o atributos.
    - No recibe parametros.
    - Devuelve un puntero a la manufactura creada.
    */
    manufactura *nueva_manufactura = (manufactura *)malloc(sizeof(manufactura));
    if (nueva_manufactura == NULL){
        printf("No se pudo crear la manufactura\n");
        exit(1);
    }

    //Incializando como null los arreglos de inventario y salida
    for (int i = 0; i < 10; i++)
    {
        nueva_manufactura->salida[i] = NULL;
        nueva_manufactura->invenrtario[i] = NULL;
    }

    //Inicializando tamanio de inventario y salida
    nueva_manufactura->tamanio = 0;
    nueva_manufactura->tamanio_salida = 0;
    nueva_manufactura->operar = NULL;

    return nueva_manufactura;
}


int *operar_suma(int *a, int *b){

    /*
    - Funcion que recibe dos punteros a enteros y devuelve un puntero a un entero con la suma de los dos enteros.
    - Recibe dos punteros a enteros.
    - Devuelve un puntero a un entero.
    */
    int *resultado = (int *)malloc(sizeof(int));
    if (resultado == NULL){
        printf("No se pudo crear el resultado\n");
        exit(1);
    }

    *resultado = *a + *b;
    return resultado;
}

int *operar_resta(int *a, int *b){
    /*
    - Funcion que recibe dos punteros a enteros y devuelve un puntero a un entero con la resta de los dos enteros.
    - Recibe dos punteros a enteros.
    - Devuelve un puntero a un entero.
    */
    int *resultado = (int *)malloc(sizeof(int));
    if (resultado == NULL){
        printf("No se pudo crear el resultado\n");
        exit(1);
    }

    *resultado = *a - *b;
    return resultado;
}

int *operar_multiplicacion(int *a, int *b){
    /*
    - Funcion que recibe dos punteros a enteros y devuelve un puntero a un entero con la multiplicacion de los dos enteros.
    - Recibe dos punteros a enteros.
    - Devuelve un puntero a un entero.

    */
    int *resultado = (int *)malloc(sizeof(int));
    if (resultado == NULL){
        printf("No se pudo crear el resultado\n");
        exit(1);
    }

    *resultado = *a * *b;
    return resultado;
}

int *operar_division(int *a, int *b){
    /* 
    - Funcion que recibe dos punteros a enteros y devuelve un puntero a un entero con la division de los dos enteros.
    - Recibe dos punteros a enteros.
    - Devuelve un puntero a un entero.
    */
    int *resultado = (int *)malloc(sizeof(int));
    if (resultado == NULL){
        printf("No se pudo crear el resultado\n");
        exit(1);
    }

    *resultado = *a / *b;
    return resultado;
}