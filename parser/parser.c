#include "../includes/minishell.h"
#include <stdio.h>


void print_str(char **s) {
	for (size_t i = 0; s[i]; i++)
	{
		printf("%s\n", s[i]);
	}
}

int main() {
	char *s = ft_strdup("echo \"hellow 'wprld'\"");
	char **splited = ft_split_parser(s, " '");
	printf("%s\n", s);
	print_str(splited);
}