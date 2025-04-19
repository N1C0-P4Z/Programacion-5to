#include <stdio.h>
#include <stdlib.h>


//ejercicio 1 

long long variableMasGrande(long long numero)
{
    return numero |= (1LL << 63) -1;
}


int cantidadDeBitsImpares(int numero)
{   
    int contador=0;
    for(int i = 0; i < 8*sizeof(int); i += 2){
        unsigned int mask = (1 << i);
        if(numero & mask)
            contador++;
    }
    return contador;
}
int main (void)
{   
    long long nro;
    printf("La variable ams grande que se puede almacenar en un long long es %lld\n", variableMasGrande(nro));
    
    int n;
    printf("Ingrese un numero entero: ");
    scanf("%d", &n);

    printf("La cantidad de bits en posiciones pares de %d son %d\n",n,cantidadDeBitsImpares(n));

    return 0;
}