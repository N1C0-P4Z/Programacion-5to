

#include <stdio.h>
#define _B (8 * sizeof(int) - 1)
int main(void)
{
    int data, c=0;
    printf("Ingrese un numero: ");
    scanf("%d", &data);

    for(unsigned int m=1<<_B; m; m >>=1)
        c+=(data &m)/m;
    printf("%d\n",c);
    printf("%d\n", _B - c + 1);
    return 0;
}