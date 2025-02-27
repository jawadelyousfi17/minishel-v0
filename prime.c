#include <stdio.h>
#include <stdlib.h>

int is_prime(int num)
{
    int i;
    i = num - 1;

    while(i > 1)
    {
        if(num % i == 0)
            return(0);
        i--;
    }
    return(1);
}

int main(int c, char **v)
{
    int i = 2;

    if(c == 2)
    {
        int num = atoi(v[1]);
        if(is_prime(num))
        {
            printf("%d\n",num);
            return(0);
        }
        while (i < num)
        {
            if((num % i == 0 && is_prime(i)) || is_prime(num))
            {
                printf("%d%s",is_prime(num) ? num :i, !is_prime(num) ? "*" : "");
                num /= i;
                i = 2;
            }
            i++;
        }
        
    }
    printf("\n");


}