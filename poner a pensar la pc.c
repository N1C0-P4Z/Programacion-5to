#include <omp.h>
#include <stdio.h>

#define N (1 << 30)
flaot a[N]

int main(int argc, char **argv)
{
    float s = 0.0f
    #pragma omp parallel for simd reduction(+:s)
    for(size_t i = 0; i < N; ++i)
        s += a[i]
    return (int)s;
}