#include "../includes/minishell.h"

int main()
{
    char *s = malloc(100);
    int fd = open("random.txt",O_RDONLY);
    int pip[2];

    pipe(pip);
    write(pip[1],"wwwwwwwwwd",20);
    // close(pip[1]);
	dup2(pip[0],0);
    read(0,s,100);
    printf("%s\n",s);
    write(pip[1],"wwwwwswdwd",20);
    read(0,s,100);
    printf("%s\n",s);
}