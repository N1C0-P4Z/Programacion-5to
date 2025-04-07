#include <stdio.h>
#include <stdlib.h>

void mostrar_permisos(int dato);
int generar_mask(int anio, char genero);

int main(void)
{
    int dato;

    printf("Ingrese el numero codificado con los permisos(0 al 255): ");
    scanf("%d", &dato);

    while(dato < 0 || dato > 255){
        printf("Ingrese un valor valido (0 al 255): ");
        scanf("%d", &dato);
    }

    mostrar_permisos(dato);



    int anio;
    char genero;

    printf("Ingrese el año (1 a 6): ");
    scanf("%d", &anio);

    while(anio < 0 || anio >6){
        printf("Ingrese un año valido(1 a 6): ");
        scanf("%d", &anio);
    }

    printf("Ingrese el genero (M/V): ");
    scanf(" %c", &genero);

    int mask = generar_mask(anio,genero);

    printf("La mascara generada que proporciona las actividades a las que se puede inscribir es: %d\n", mask);
    return 0;
}

void mostrar_permisos(int dato)
{
    printf("Genero permitido:\n");
    if(dato & (1 << 7))
        printf("Hombres\n");
    if(dato & (1 << 6))
        printf("Mujeres\n");

    printf("Años permitidos:\n");
    int anio = 0;

    for(int i = 0; i < 6; i++){
        if(dato & (1 << i)){
            printf("%d ", i + 1);
            anio = 1;
        }
    }

    if(!anio)
        printf("Ninguno\n");
    printf("\n");
}

int generar_mask(int anio, char genero)
{
    int mask = 0;

    mask |= (1 << (anio - 1));

    if(genero == 'V' || genero == 'H' || genero == 'v' || genero == 'h'){
        mask |= 1 << 7;
    }else if(genero == 'M' || genero == 'F' || genero == 'm' || genero == 'f'){
        mask |= 1 << 6;
    }else{
        printf("Genero no valido\n");
    }
    return mask;
}
