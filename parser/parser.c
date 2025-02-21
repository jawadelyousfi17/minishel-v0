#include "../includes/minishell.h"
#include <stdio.h>


void print_str(char **s) {
	for (size_t i = 0; s[i]; i++)
	{
		printf("%s\n", s[i]);
	}
}

int main() {
	char *s = ft_strdup("< infile ls | echo \"hello world 'How are you'\" | ls -la | grep \"Hello\" > \"outfile\"");
	char **splited = ft_split(s, ' ');
	printf("%s\n", s);
	print_str(splited);
}