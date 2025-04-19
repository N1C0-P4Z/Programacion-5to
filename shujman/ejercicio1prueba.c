#include <stdio.h>
#include <stdlib.h>


long long numeroMasGrande()
{
    long long numero = (1ll << 63);
    return ~numero;
}

void imprimirbits(long long numero){
    for(int i = 63; i>=0; i--){
        long long mask = 1LL << i;
        printf("%d", (numero & mask)? 1 : 0);

        if(i % 8 == 0)
            printf(" ");
    }
}
int main (void)
{   
    long long numero = (1LL << 63) -1;
    printf("El entero positivo mas grande que se puede almacenar en un long long es: %lld\n", numeroMasGrande());
    printf("Los bits de %lld:\n", numero);
    imprimirbits(numero);

    return 0;   
}


