#include "utils.h"


static int	count_words(char const *str, char c)
{
	int	in_word;
	int	counter;

	counter = 0;
	in_word = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
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

static char	**zero_last(char **splited_strings, int index)
{
	splited_strings[index] = 0;
	return (splited_strings);
}

char	**ft_split(char const *s, char c, int flag)
{
	char	**splited_string;
	int		start_index;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	start_index = 0;
	splited_string = (char **)ft_malloc((count_words(s, c) + 1) * sizeof(char *), flag);
	if (!splited_string)
		return (NULL);
	while (s && *s)
	{
		start_index = 0;
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		while (*s && *s != c && ++start_index)
			s++;
		splited_string[index] = ft_substr(s - start_index, 0, start_index, flag);
		if (!splited_string[index++])
			return (NULL);
	}
	return (zero_last(splited_string, index));
}