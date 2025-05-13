#include <stdio.h>
#include <stdlib.h>

void estadoActual(unsigned int dato);

unsigned int cambiar1Bomba(unsigned int dato);
unsigned int cambiar_todas_bombas(unsigned int dato);

int main (void)
{   
    unsigned int dato;
    printf("Ingrese el dato codificado de las bombas: ");
    scanf("%u", &dato);

    int opcion;
    do{
        printf("El estado actual de las bombas es:\n");
        estadoActual(dato);

        printf("1: Cambiar la Configuracion de una bomba\n");
        printf("2: Cambiar la configuracion de todas las bombas\n");
        printf("0: Salir\n");

        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            dato = cambiar1Bomba(dato);
            break;
        case 2:
            dato = cambiar_todas_bombas(dato);
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

void estadoActual(unsigned int dato)
{
    int mask = 15;

    for(int i = 0; i < 8; i++){
        int actual = dato & mask;
        printf("El estado de la bomba %i es: Nivel:%d (Caudal%d)\n", i, actual, (actual * 100)/16);
        dato >>= 4;

    }
}

unsigned int cambiar1Bomba(unsigned int dato)
{
    int nroBomba, nuevoNivel;

    printf("Ingrese el numero de bomba a cambiar: ");
    scanf("%d", &nroBomba);

    while(nroBomba < 0 || nroBomba > 7){
        printf("Numero de Bomba Invalido. Ingrese un numero de 0 - 7: ");
        scanf("%d", &nroBomba);
    }

    printf("Ingrese el nuevo nivel: ");
    scanf("%d", &nuevoNivel);

    while(nuevoNivel < 0 || nuevoNivel > 15){
        printf("Nivel Invalido. Ingrese un nivel de 0 - 15: ");
        scanf("%d", &nuevoNivel);
    }

    unsigned int mascara = 15 << (nroBomba * 4);

    dato &= ~mascara;
    dato |= (nuevoNivel << (nroBomba * 4));

    return dato;
}

unsigned int cambiar_todas_bombas(unsigned int dato)
{   
    int nuevo_nivel;

    printf("Ingrese el nuevo nivel a cambiar todas las bombas: ");
    scanf("%d", &nuevo_nivel);

    while(nuevo_nivel < 0 || nuevo_nivel > 15){
        printf("Nivel Invalido. Ingrese un nivel del 0 - 15: ");
        scanf("%d", &nuevo_nivel);
    }

    for(int i = 0; i < 8; i++){
        dato = dato << 4;
        dato |= nuevo_nivel;
    }
    return dato;
}
