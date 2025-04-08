#include <stdio.h>
#include <stdlib.h>

#define largo (8*sizeof(int)-1)

int main(void)
{   
    int n;
    printf("Ingrese un numero: ");
    scanf("%d", &n);

    for(unsigned int mask = 1 << largo; mask;mask >>= 1)
        printf("%i", (n & mask) ? 1 : 0);
    
    return 0;
}