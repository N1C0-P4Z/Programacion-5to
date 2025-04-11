#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void permisos(unsigned char dato);
int devolverpermisos(char genero, int anio);

int main (void)
{   
    unsigned char dato;

    printf("Ingrese el numero con los permisos codificados: ");
    scanf("%hhu", &dato);

    permisos(dato);

    int anio;
    char genero;


    printf("Ingrese el genero del alumno a generar la mascara: ");
    scanf(" %c", &genero);


    printf("Ingrese el año del alumno a generar la mascara: ");
    scanf("%d", &anio);
    while(anio < 0 || anio > 6){
        printf("Año invalido. Por favor ingrese correctamente el año (1 - 6): ");
        scanf("%d", &anio);
    }

    printf("La mascara del alumno %c de %d año es %d\n",genero,anio, devolverpermisos(genero, anio));

    return 0;
}

void permisos(unsigned char dato)
{   
    int existe = 0;
    printf("Genero permitido:\n");

    if (dato & (1 << 7))
        printf("Masculino\n");
    if (dato & (1 << 6))
        printf("Femenino\n");

    printf("Año permitido:\n");

    for(int i = 0; i < 6; i++){
        if(dato & (1 << i)){
            printf("%d ", i + 1);
            existe = 1;
        }
    }

    if(existe == 0)
        printf("Ninguno\n");

    printf("\n");
    
}

int devolverpermisos(char genero, int anio)
{
    int mask = 0;

    mask |= (1 << (anio - 1));


    if(toupper(genero) == 'V' || toupper(genero) == 'H')
        mask |= (1 << 7);
    if(toupper(genero) == 'F' || toupper(genero) == 'M')
        mask |= (1 << 6);
    return mask;
}
