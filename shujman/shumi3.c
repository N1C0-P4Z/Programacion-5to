#include <stdio.h>
#include <stdlib.h>

void actualBombas(unsigned int dato);
unsigned int cambiarUnaBomba(unsigned int dato);
unsigned int cambiarTodasBombas(unsigned int dato);

int main (void)
{   
    unsigned int dato;

    printf("Ingrese un entero que indique el estado de las 8 bombas: ");
    scanf("%d", &dato);

    int opcion;

    do{
        printf("El estado actual de las bombas es:\n");
        actualBombas(dato);

        printf("1: Cambiar la Configuracion de una bomba\n");
        printf("2: Cambiar la configuracion de todas las bombas\n");
        printf("0: Salir\n");

        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            dato = cambiarUnaBomba(dato);
            break;
        case 2:
            dato = cambiarTodasBombas(dato);
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida, ingrese correctamente\n");
        }

        printf("\n");
    }while(opcion != 0);


    return 0;
}



void actualBombas(unsigned int dato)
{
    int mask = 15;

    for(int i = 0; i < 8; i++)
    {
        int bomba_actual = dato & mask;
        printf("Bomba %d: Nivel %d (Caudal %d%)\n", i, bomba_actual, (bomba_actual * 100)/16);
        dato >>= 4;
    }
}

unsigned int cambiarUnaBomba(unsigned int dato)
{
    int numero_bomba, nuevo_nivel;

    printf("Ingrese el numero de bomba del 0 al 7: \n");
    scanf("%d", &numero_bomba);

    while(numero_bomba < 0 || numero_bomba > 7){
        printf("Ingrese un numero valido del 0 al 7: \n");
        scanf("%d", &numero_bomba);
    }

    printf("Ingrese el nuevo nivel del 0 al 15: \n");
    scanf("%d", &nuevo_nivel);

    while(nuevo_nivel < 0 || nuevo_nivel > 15){
        printf("Ingrese un numero valido del 0 al 15: \n");
        scanf("%d", &nuevo_nivel);
    }

    unsigned int mask = 15 << (numero_bomba * 4);

    dato -= (dato & mask);
    dato += (nuevo_nivel << (numero_bomba * 4));

    return dato;
}

unsigned int cambiarTodasBombas(unsigned int dato)
{

    int nuevo_nivel;

    printf("Ingrese el nuevo nivel del 0 al 15: \n");
    scanf("%d", &nuevo_nivel);

    while(nuevo_nivel < 0 || nuevo_nivel > 15){
        printf("Ingrese un numero valido del 0 al 15: \n");
        scanf("%d", &nuevo_nivel);
    }

    dato = nuevo_nivel;
    for(int i = 0; i < 7; i++){
        dato <<= 4;
        dato +=  nuevo_nivel;
    }

    return dato;
}
