#include "Io.h"
#include "Manufactura.h"
#include "Robot.h"
#include "Mundo.h"
#include "stdio.h"
#include "stdlib.h"

//declaracion de variables globales
void **mundo;
int tamano_mundo;

//Validador de opcion 

int obtenerNumero() {
    /*
    - Funcion que permite validar que la opcion ingresada sea un numero y no un caracter.
    - No recibe parametros.
    - Devuelve un numero entero.
    */

    int numero;
    while (scanf("%d", &numero) != 1) {
        printf("Ingrese una opcion valida: ");
        while (getchar() != '\n');
    }
    return numero;
}




void construir(){

    /*
    - Funcion que permite al usuario construir una estructura en una casilla del mundo preguntandole la cordenada 
    y el tipo de estructura que desea construir.

    - No recibe parametros.
    - No devuelve nada.
    */

    int opcion, cordenada, direccion;

    printf("Ingrese Cordenada: ");
    cordenada = obtenerNumero();

    //caso en que la cordenada no sea valida
    if (cordenada < 0 || cordenada >= tamano_mundo){
        printf("Cordenada no valida\n");
        return;
    }

    printf("Ingrese una opcion para construir\n");
    printf("1. Robot\n");
    printf("2. Manufactura\n");
    printf("3. Salir\n");

    printf(">> ");
    opcion = obtenerNumero();

    switch(opcion)
    {
        case 1:
            printf("Direccion inicial\n");
            printf("0.- IZQ\n");
            printf("1.- DER\n");
            printf(">> ");
            direccion = obtenerNumero();

            if (direccion != 0 && direccion != 1){
                printf("Direccion incicial no valida :P\n");
                break;
            }

            //Verificndo si ya existe una estructura en la casilla
            if (((casilla *)mundo[cordenada])->tipo_estructura != ' '){
                printf("Ya existe una estructura en la casilla\n");
                break;
            }

            //Creando robot
            robot *nuevo_robot = crear_robot();
            nuevo_robot->direccion = direccion;
            ((casilla *)mundo[cordenada])->tipo_estructura = 'R';
            ((casilla *)mundo[cordenada])->estructura = nuevo_robot;
            printf("Robot creado\n");



            break; 
        case 2:
            printf("Selecciona una operacion\n");
            printf("1. Suma\n");
            printf("2. Resta\n");
            printf("3. Multiplicacion\n");
            printf("4. Division\n");
            printf(">> ");

            scanf("%d", &opcion);
            if (opcion < 1 || opcion > 4){
                printf("Operacion no valida\n");
                break;
            }

            //Verificando si ya existe una estructura en la casilla

            if (((casilla *)mundo[cordenada])->tipo_estructura != ' '){
                printf("Ya existe una estructura en la casilla\n");
                break;
            }

            //Creando manufactura
            manufactura *nueva_manufactura = crear_manufactura();
            
            if (opcion == 1){
                nueva_manufactura->operar = operar_suma;
            }
            else if (opcion == 2){
                nueva_manufactura->operar = operar_resta;
            }
            else if (opcion == 3){
                nueva_manufactura->operar = operar_multiplicacion;
            }
            else if (opcion == 4){
                nueva_manufactura->operar = operar_division;
            }

            ((casilla *)mundo[cordenada])->tipo_estructura = 'M';
            ((casilla *)mundo[cordenada])->estructura = nueva_manufactura;



            break;
        case 3:
            printf("Saliendo\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
    }


}

void destruir()
{
    /*
    - Funcion que permite al usuario destruir una estructura en una casilla del mundo preguntandole la cordenada de la estructura que desea destruir.
    - No recibe parametros.
    - No devuelve nada.
    */
    int coordenada;
    printf("Ingrese la coordenada de la estructura que desea eliminar: ");
    coordenada = obtenerNumero();

    //caso en que la cordenada no sea valida
    if (coordenada < 0 || coordenada >= tamano_mundo){
        printf("Cordenada no valida\n");
        return;
    }



    //caso en que la casilla este vacia
    if (((casilla *)mundo[coordenada])->tipo_estructura == ' '){
        printf("Casilla vacia\n");
        return;
    }

    //caso en que la casilla tenga un robot
    if (((casilla *)mundo[coordenada])->tipo_estructura == 'R'){
        free(((robot *)((casilla *)mundo[coordenada])->estructura)->inventario);
        free(((casilla *)mundo[coordenada])->estructura);
        ((casilla *)mundo[coordenada])->tipo_estructura = ' ';
        ((casilla *)mundo[coordenada])->estructura = NULL;
        printf("Robot destruido\n");
        return;
    }

    //caso en que la casilla tenga una manufactura
    if (((casilla *)mundo[coordenada])->tipo_estructura == 'M'){
        //IMPORTANTE:  no olvidar liberar memoria de los arreglos de inventario y salida, y de la manufactura
        free(((manufactura *)((casilla *)mundo[coordenada])->estructura));
        ((casilla *)mundo[coordenada])->tipo_estructura = ' ';
        ((casilla *)mundo[coordenada])->estructura = NULL;
        printf("Manufactura destruida\n");
        
    }

    //caso en que la casilla tenga una estructura de I/O
    if (((casilla *)mundo[coordenada])->tipo_estructura == 'I' || ((casilla *)mundo[coordenada])->tipo_estructura == 'O'){
        if (((io *)((casilla *)mundo[coordenada])->estructura)->entrada_o_salida == 'I'){
            printf("ERROR: NO Puede destruir la entrada\n");
        }
        else{
            printf("ERROR: NO Puede destruir la salida\n");
        }
    }


}

void informacion()
{
    /*
    - Funcion que permite al usuario obtener informacion de una estructura en una casilla del mundo preguntandole la cordenada de la estructura que desea obtener informacion.
    - No recibe parametros.
    - No devuelve nada.
    */

    int cordenada;
    printf("Ingrese una cordenada: ");
    cordenada = obtenerNumero();

    //caso en que la cordenada no sea valida
    if (cordenada < 0 || cordenada >= tamano_mundo){
        printf("Cordenada no valida\n");
        return;
    }

    //caso en que la casilla este vacia
    if (((casilla *)mundo[cordenada])->tipo_estructura == ' '){
        printf("Casilla vacia\n");
        return;
    }

    //caso en que la casilla tenga un robot
    if (((casilla *)mundo[cordenada])->tipo_estructura == 'R'){
        printf("Robot\n");
        printf("Direccion: %s\n", ((robot *)((casilla *)mundo[cordenada])->estructura)->direccion == 0 ? "IZQ" : "DER");

        if (((robot *)((casilla *)mundo[cordenada])->estructura)->tiene_inventario == 'Y'){
            printf("Inventario: %d\n", *((robot *)((casilla *)mundo[cordenada])->estructura)->inventario);
        }else{
            printf("Inventario: NO\n");
        }
        return;
    }

    //caso en que la casilla tenga una manufactura
    if (((casilla *)mundo[cordenada])->tipo_estructura == 'M'){
        printf("Manufactura\n");
        printf("Operacion: ");
        if (((manufactura *)((casilla *)mundo[cordenada])->estructura)->operar == operar_suma)
            printf("Suma\n");
        if (((manufactura *)((casilla *)mundo[cordenada])->estructura)->operar == operar_resta)
            printf("Resta\n");
        if (((manufactura *)((casilla *)mundo[cordenada])->estructura)->operar == operar_multiplicacion)
            printf("Multiplicacion\n");
        if (((manufactura *)((casilla *)mundo[cordenada])->estructura)->operar == operar_division)
            printf("Division\n");
        
        if (((manufactura *)((casilla *)mundo[cordenada])->estructura)->tamanio == 0){
            printf("Inventario: VACIO\n");
        }else{

            printf("Tamanio de inventario: %d\n", ((manufactura *)((casilla *)mundo[cordenada])->estructura)->tamanio);
        }
        printf("Tamanio de salida: %d\n", ((manufactura *)((casilla *)mundo[cordenada])->estructura)->tamanio_salida);
        return;
    }

    //caso en que la casilla tenga una estructura de I/O

    if (((casilla *)mundo[cordenada])->tipo_estructura == 'I' || ((casilla *)mundo[cordenada])->tipo_estructura == 'O'){
        printf(">> I/O\n");

        if (((io *)((casilla *)mundo[cordenada])->estructura)->entrada_o_salida == 'I'){
            printf("Tipo: ENTRADA\n");
        }
        else{
            printf("Tipo: SALIDA\n");
        }

        if (((io *)((casilla *)mundo[cordenada])->estructura)->objeto != NULL){
            printf("Objeto: %d\n", *((io *)((casilla *)mundo[cordenada])->estructura)->objeto);
        }
        else{
            printf("Objeto: NULL\n");
        }
        return; 
    }


}



void salir()
{
    /*
    - Funcion que permite al usuario salir del programa, borrnado el mundo y liberando la memoria.
    - No recibe parametros.
    - No devuelve nada.
    */
    borrar_mundo();
    printf("Hasta luego\n");
    exit(0);

}

int main()
{

    

   printf("Bienvenido a la fabrica de numeros\n");

    int opcion, ticks;

    
    printf("Ingrese el tamanio del mundo: ");
    tamano_mundo = obtenerNumero();

    
    
    crear_mundo(tamano_mundo);
    //tamanio del mundo minimo 3
    if (tamano_mundo < 5){
        printf("Tamanio del mundo no valido\n");
        exit(1);
    }


    printf("Mundo creado\n");
    

    do
    {
        mostrar_mundo();
        printf("1. Construir\n");
        printf("2. Destruir\n");
        printf("3. Informacion\n");
        printf("4. Simular\n");
        printf("5. Salir\n");
        printf("Ingrese una opcion: ");
        //validando que la opcion sea un numero y no un caracter
        opcion = obtenerNumero();

        switch(opcion)
        {
            case 1:
                construir();
                break;
            case 2:
                destruir();
                break;
            case 3:
                informacion();
                break;
            case 4:
                printf("Ingrese el numero de ticks: ");
                printf(">> ");
                ticks = obtenerNumero();
                simular(ticks);
                break;
            
            case 5:
                salir();
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    } while(opcion != 5);


    return 0;
}
