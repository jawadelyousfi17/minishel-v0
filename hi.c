#include <libc.h>
#include <fcntl.h>

int main(int ac, char **av)
{
    int fd1 = open("test1",O_RDWR);
    int fd = dup(1);
    dup2(fd1,fd);
    write(fd,"lol",3);
    write(1,"hh",2);
}