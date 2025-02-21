
#include "../includes/minishell.h"

static int	is_charset(char c, char *charset)
{
	if (!charset)
		return (0);
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	count_words(char const *str, char *charset)
{
	int	in_word;
	int	counter;

	counter = 0;
	in_word = 0;
	while (*str)
	{
		while (*str && is_charset(*str, charset))
			str++;
		while (*str && !is_charset(*str, charset))
		{
			str++;
			in_word = 1;
		}
		if (in_word)
		{
			counter++;
			in_word = 0;
		}
	}
	return (counter);
}

static char	**__free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (NULL);
}

static char	**zero_last(char **splited_strings, int index)
{
	splited_strings[index] = 0;
	return (splited_strings);
}

char	**ft_split_parser(char const *s, char *ch)
{
	char	**splited_string;
	int		start_index;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	start_index = 0;
	splited_string = (char **)malloc((count_words(s, ch) + 1) * sizeof(char *));
	if (!splited_string)
		return (NULL);
	while (s && *s)
	{
		start_index = 0;
		while (*s && is_charset(*s, ch))
			s++;
		if (!*s)
			break ;
		while (*s && !is_charset(*s, ch) && ++start_index)
			s++;
		splited_string[index] = ft_substr(s - start_index, 0, start_index);
		if (!splited_string[index++])
			return (__free(splited_string));
	}
	return (zero_last(splited_string, index));
}
