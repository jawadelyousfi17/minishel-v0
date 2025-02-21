/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:37:45 by zbouchra          #+#    #+#             */
/*   Updated: 2025/01/01 22:45:51 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_index(const char *str, int *s)
{
	int	i;

	i = 0;
	*s = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		*s *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	r;
	int		s;
	int		i;
	long	r1;

	r = 0;
	s = 1;
	i = get_index(str, &s);
	while (ft_isdigit(str[i]))
	{
		r1 = r;
		r = r * 10 + (str[i] - '0');
		if (r / 10 != r1 && s == 1)
			return (-1);
		if (r / 10 != r1 && s == -1)
			return (0);
		i++;
	}
	return ((int)r * s);
}
