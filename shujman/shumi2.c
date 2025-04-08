#include <stdio.h>
#include <stdlib.h>

#define mask_temp 255
#define mask_hum 127
#define mask_pre 2047


void instrumentoA(int dato);
void everestB(int dato);
void fallaC(int dato);

int main(void)
{   
    int dato;

    printf("Ingrese las mediciones codificadas: ");
    scanf("%d", &dato);

    instrumentoA(dato);
    /*everestB(dato);*/
    /*fallaC(dato);*/
    
    return 0;
}

void instrumentoA(int dato)
{
    int temp_aux = dato & mask_temp;
    int temperatura = (temp_aux < 128) ? temp_aux : temp_aux - 256;
    unsigned int humedad = (dato >> 8) & mask_hum;
    unsigned int presion = (dato >> 15) & mask_pre;
    
    printf("La temperatura es: %d \n", temperatura); 
    printf("La humedad es: %d\n",humedad);
    printf("La presion es: %d\n", presion);
}

void everestB(int dato)
{
    int temp_aux = dato & mask_temp;
    int temperatura = (temp_aux < 128) ? temp_aux : temp_aux - 256;
    
    int presion = (dato >> 15) & mask_pre;

    if(temperatura < -70 || presion < 382){
        printf("ERROR DE LECTURA\n");
    }else{
        printf("La temperatura es: %d °C\n", temperatura);
        printf("La presión es: %d Hpa\n”", presion);
    }
}

void fallaC(int dato)
{
    int estado = (dato >> 26);
    if(estado & 1){
        int temp_aux = dato & mask_temp;
        int temperatura = (temp_aux < 128) ? temp_aux : temp_aux - 256;
        printf("La temperatura es: %d °C\n", temperatura);
    }else{
        printf("El instrumento que mide la temperatura FALLA\n");
    }

    if(estado & 2){
        int humedad = (dato >> 8) & mask_hum;
        printf("La humedad es: %d %\n", humedad);
    }else{
        printf("El instrumento que mide la humedad FALLA\n");
    }

    if(estado & 4){
        int presion = (dato >> 15) & mask_pre;
        printf("La presion es:%d Hpa\n",presion);
    }else{
        printf("El instrumento que mide la presion falla");
    }
}
