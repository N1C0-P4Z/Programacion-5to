#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hexaDec(char hexa);
void hexAscii (void);

void decHexa(int numero, char hexa[], int posicion);
void asciiHexa(void);

int main (void)
{   

    while(1){
        int opcion;
        printf("Ingrese la opcion que quiere hacer\n");
        printf("0 - Salir\n");
        printf("1 - Pasar un valor hexa a ASCII\n");
        printf("2 - Pasar un valor ASCII a hexa\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        switch(opcion){
            case 0: 
                return 0;
            case 1:
                hexAscii();
                break;
            case 2:
                asciiHexa();
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }
    }
}

int hexaDec(char hexa)
{
    if(hexa >= '0' && hexa <= '9') return hexa - '0';
    hexa = tolower(hexa);
    if(hexa >= 'a' && hexa <= 'f') return hexa - 'a' + 10;
    return -1;
}

void hexAscii(void)
{  
    char hexa[32];

    printf("Ingrese un valor en Hexa: ");
    scanf("%s", hexa);

    int i = 0;

    if (hexa[0] == '0' && (hexa[1] == 'x' || hexa[1] == 'X')) {
        i = 2;
    }

    while(hexa[i] && hexa[i + 1]){
        int left = hexaDec(hexa[i]);
        int rigth = hexaDec(hexa[i + 1]);

        if (left == -1 || rigth == -1) {
            printf("\nError: caracter hexa no válido: %c%c\n", hexa[i], hexa[i + 1]);
            return;
        }

        char resultado = (left << 4) | rigth;
        printf("%c", resultado);
        i += 2;
    }
    printf("\n");
}


void decHexa(int numero, char hexa[], int posicion)
{   
    if(numero >9 && numero < 16){
        hexa[posicion] = 'A' + (numero - 10);
    } else if(numero < 10 && numero > -1){
        hexa[posicion] = '0' + numero;
    }else{
        printf("El ASCCI no es valido\n");
    }
}

void asciiHexa(void)
{
    int ascii[30] = {0};
    int i;

    for(i = 0; i < 30; i++){
        printf("Ingrese el valor en ASCII de la letra [%d] (si ingresa -1 termina el programa): ", i + 1);
        scanf("%d", &ascii[i]);

        if(ascii[i] == -1)
            break;
    }

    int leng = i;
    char hexa[62] = {0};
    hexa[0] = '0', hexa[1] = 'x';
    int posicion = 2;

    for(int j = 0; j < leng; j++,posicion +=2){
        int left = (ascii[j] & 240) >> 4;
        int rigth = (ascii[j] & 15);

        decHexa(left, hexa, posicion);
        decHexa(rigth, hexa, posicion + 1);
    }

    printf("\n");

    for(int k = 0; k < posicion; k++){
        printf("%c", hexa[k]);
    }

    printf("\n");
}
