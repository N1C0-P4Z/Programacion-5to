#include <stdio.h>
#include <stdlib.h>

#define mask_temperatura  255
#define mask_humedad  127
#define mask_presion  2047

void puntoA(int dato);
void puntoB(int dato);
void puntoC(int dato);

int main(void)
{   
    int dato;
    printf("Ingrese las mediciones codificadas: ");
    scanf("%d", &dato);

    puntoA(dato);
    puntoB(dato);
    puntoC(dato);
    return 0;  
}

void puntoA(int dato)
{
    int temp_aux = dato & mask_temperatura;
    int temperatura = (temp_aux < 128) ? temp_aux : (temp_aux - 256);
    unsigned int humedad = (dato >> 8) & mask_humedad;
    unsigned int presion = (dato >> 15) & mask_presion;
    
    printf("La temperatura es: %d\n", temperatura);
    printf("La humedad es: %d\n", humedad);
    printf("La presion es: %d\n",presion);

}

void puntoB(int dato)
{
    int temp_aux = dato & mask_temperatura;
    int temperatura = (temp_aux < 128) ? temp_aux : (temp_aux - 256);
    unsigned int presion = (dato >> 15) & mask_presion;

    if(temperatura < -70 || presion < 382){
        printf("ERROR DE LECTURA\n");
    }else{
        printf("La temperatura es: %d\n", temperatura);
        printf("La presion es: %d\n",presion);
    }
}

void puntoC(int dato)
{
    int estado = (dato >> 26);
    if(estado & 1){
        printf("El instrumento que mide la temperatura FALLA\n");
    }else{
        int temp_aux = dato & mask_temperatura;
        int temperatura = (temp_aux < 128) ? temp_aux : temp_aux - 256;
        printf("La temperatura es: %d °C\n", temperatura);
    }


    if(estado & 2){
        printf("El instrumento que mide la humedad FALLA\n");
    }else{
        int humedad = (dato >> 8) & mask_humedad;
        printf("La humedad es: %d\n", humedad);
    }

    if(estado & 4){
        printf("El instrumento que mide la presion FALLA\n");
    }else{
        int presion = (dato >> 15) & mask_presion;
        printf("La presion es:%d Hpa\n",presion);
    }

}
