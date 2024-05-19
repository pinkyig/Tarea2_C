#include "Robot.h"
#include "Manufactura.h"
#include "Io.h"
#include "Mundo.h"
#include <stdio.h>
#include <stdlib.h>





robot *crear_robot(){

    /*
    - Funcion que crea un robot y lo inicializa con sus atributos.
    - No recibe parametros.
    - Devuelve un puntero a un nuevo robot. 
    */

    robot *nuevo_robot = (robot *)malloc(sizeof(robot));
    if (nuevo_robot == NULL){
        printf("No se pudo crear el robot\n");
        exit(1);
    }

    //Inicializando robot

    nuevo_robot->inventario = NULL;
    nuevo_robot->tiene_inventario = 'N';
    nuevo_robot->direccion = 0;

    return nuevo_robot;
    
}


void interactuar_io(io *io, robot *rob){

    /*
    - Funcion que permite al robot interactuar con la estructura de entrada o salida.
    - Recibe un puntero a la estructura de entrada o salida y un puntero al robot.
    - No devuelve nada.
    */
    //Caso en que la estructura sea de entrada: I le pasa un 1 del inventario al robot y crea otro 1 en la entrada
    if (io->entrada_o_salida == 'I'){
        printf("Robot interactua con entrada\n");
        if (rob->tiene_inventario == 'N'){
            rob->inventario = (int *)malloc(sizeof(int));
            if (rob->inventario == NULL){
                printf("No se pudo crear el inventario\n");
                exit(1);
            }
            *rob->inventario = *io->objeto;
            rob->tiene_inventario = 'Y';
            rob->direccion = 1;
            *io->objeto = 1;
            
        }else{
            printf("El robot ya tiene un objeto\n");
            rob->direccion = 1;
        }
    }else{
        //Caso en que la estructura sea de salida: O recibe el objeto del robot y lo pone en la salida
        printf("Robot interactua con salida\n");
        if (rob->tiene_inventario == 'Y'){
            io->objeto = rob->inventario;
            printf("Numero entregado >> %d\n", *io->objeto);
            free(rob->inventario);
            rob->tiene_inventario = 'N';
            rob->inventario = NULL;
            rob->direccion = 0;

            //destruyendo el objero entregado
            io->objeto = NULL;
            
        }else{
            printf("El robot no tiene nada que entregar\n");
            rob->direccion = 0;
        }
    }

}


void interactuar_manufactura(manufactura *manf, robot *rob){
    /*
    - Funcion que permite al robot interactuar con la estructura de manufactura.
    - Recibe un puntero a la estructura de manufactura y un puntero al robot.
    - No devuelve nada.
    */
    //Caso en que el robot no tiene inventario
    if (rob->tiene_inventario == 'N'){
        //si tiene el inventario vacıo, intentara extraer un numero
        if (manf->tamanio == 0){
            printf("Robot sin inventario y no hay nada que extraer de la Manufactura\n");
        }
        

    }else{
        //Caso en que el robot tiene inventario
        printf("El robot tiene inventario\n");
        if (manf->tamanio < 10){
            printf("Se agrega el inventario a la manufactura\n");
            manf->tamanio++;
            free(rob->inventario);
            rob->inventario = NULL;
            rob->tiene_inventario = 'N';
        }else{
            printf("No se puede agregar mas inventario\n");
        }
    }
}


void step_robot(void *estructura, int x){
    /*
    - Funcion que permite al robot moverse en el mundo en la direccion en la que esta mirando y depediendo de la siguiente casilla en la que se va a mover interactua con la estructura de la casilla.
    */
    //Caso en que el robot se mueve a la derecha
    if (((robot *)estructura)->direccion == 1){
        if (((casilla *)mundo[x + 1])->tipo_estructura == 'O'){
            interactuar_io(((casilla *)mundo[x + 1])->estructura, estructura);
        }

        if (((casilla *)mundo[x + 1])->tipo_estructura == ' '){
            ((casilla *)mundo[x + 1])->tipo_estructura = 'R';
            ((casilla *)mundo[x + 1])->estructura = estructura;
            ((casilla *)mundo[x])->tipo_estructura = ' ';
            ((casilla *)mundo[x])->estructura = NULL;

            
        }else if (((casilla *)mundo[x + 1])->tipo_estructura == 'M'){
            interactuar_manufactura(((casilla *)mundo[x + 1])->estructura, estructura);
            ((robot *)estructura)->direccion = 0;
        }
        else if (((casilla *)mundo[x + 1])->tipo_estructura != ' '){
            
            ((robot *)estructura)->direccion = 0;
        }




    }//Caso en que el robot se mueve a la izquierda
    else{
        if (((casilla *)mundo[x - 1])->tipo_estructura == 'I'){
            interactuar_io(((casilla *)mundo[x - 1])->estructura, estructura);
        }

        if (((casilla *)mundo[x - 1])->tipo_estructura == ' '){
            ((casilla *)mundo[x - 1])->tipo_estructura = 'R';
            ((casilla *)mundo[x - 1])->estructura = estructura;
            ((casilla *)mundo[x])->tipo_estructura = ' ';
            ((casilla *)mundo[x])->estructura = NULL;
            
        }else if (((casilla *)mundo[x - 1])->tipo_estructura != ' '){
                
                ((robot *)estructura)->direccion = 1;
        }
    }

}