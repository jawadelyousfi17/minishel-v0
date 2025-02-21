/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:33:08 by zbouchra          #+#    #+#             */
/*   Updated: 2025/01/20 00:46:42 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 1;
	count = 0;
	while (s[i])
	{
		if (j == 1 && s[i] != c)
		{
			count++;
			j = 0;
		}
		if (j == 0 && s[i] == c)
			j = 1;
		i++;
	}
	return (count);
}

void	free_strings(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
}

static char	**split_string(int a, char c, char **str, char *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < a)
	{
		k = 0;
		j = 0;
		while (s[k] && s[k] == c)
			k++;
		while (s[j + k] && s[j + k] != c)
			j++;
		str[i] = ft_substr(s, k, j);
		if (!str[i])
		{
			free_strings(str, i);
			return (NULL);
		}
		s = &s[j + k];
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	if (!s || !*s)
		return (NULL);
	count = count_words(s, c);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (!split_string(count, c, str, (char *)s))
		return (NULL);
	str[count] = NULL;
	return (str);
}
