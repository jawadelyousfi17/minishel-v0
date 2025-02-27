#include <libc.h>

void skip_white(char **s)
{
    while (**s && (**s == ' ' || **s == '\t'))
    {
        (*s)++;
    }
}

void skip_word(char **s, int flag)
{
    while (**s && (**s != ' ' && **s != '\t'))
    {
        if (flag == 1)
            write(1, *s, 1);
        (*s)++;
    }
}


unsigned char swap_bits(unsigned char octet)
{
    return(octet <<  4 | octet >> 4);
}

void print_bits(unsigned char octet)
{
    char c;
    int i = 0;
    while(i < 8)
    {
        if(octet & 128)
            write(1,"1",1);
        else
            write(1,"0",1);
        octet = octet << 1;
        i++;
    }
}
unsigned char	reverse_bits(unsigned char octet)
{
	int				idx;
	unsigned char	res;

	idx = 8;
	res = 0;
	while (idx > 0)
	{
		res = res * 2 + (octet % 2);
		octet /= 2;
		idx--;
	}
	return (res);
}
int main(int ac, char **av)
{
    // int i = 0;
    // char *s = av[1];

    // skip_white(&s);
    // skip_word(&s, 0);
    // skip_white(&s);
    // while (*s)
    // {
    //     skip_white(&s);
    //     skip_word(&s, 1);
    //     skip_white(&s);
    //     write(1, " ", 1);
    // }
    // s = av[1];
    // skip_white(&s);
    // skip_word(&s, 1);
    unsigned char octet = 0b01010101;
    // unsigned char s = swap_bits(octet);
    print_bits(octet);
    write(1,"\n",1);
    octet = reverse_bits(octet);
    print_bits(octet);

    
}