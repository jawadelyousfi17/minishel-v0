#include "../includes/minishell.h"

#ifndef MALLOC
    #define malloc(x) ft_malloc(x,0);
#endif

void foo(){system("leaks a.out");}

int main()
{
    atexit(foo);
    char *s = (char *)malloc(100);
    s = (char *)malloc(100);
    s = (char *)malloc(100);
    s = (char *)malloc(100);
    s = (char *)malloc(100);
    s = (char *)malloc(100);
    s = (char *)malloc(100);
    s = (char *)malloc(100);
    // ft_malloc(0,1);
}
