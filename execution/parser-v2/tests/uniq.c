#include <stdio.h>

int main()
{
    size_t i = 0;
    for (size_t i = 100; i < 110; i++)
        printf("%ld\n", (i * 250) ^ (i << 3));
}