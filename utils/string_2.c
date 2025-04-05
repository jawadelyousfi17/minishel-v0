/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:11:29 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:26:03 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_equal(char *s, char *p)
{
	if (ft_strlen(s) != ft_strlen(p))
		return (0);
	return (ft_strncmp(s, p, ft_strlen(p)) == 0);
}

char	*ft_strndup(char *s, size_t len, int flag)
{
	char	*r;
	size_t	i;

	i = 0;
	r = ft_malloc(len + 1, flag);
	if (!r)
		return (NULL);
	while (s[i] && i < len)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = 0;
	return (r);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}
