/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:11:32 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:25:46 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	get_int_size(long int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n, int flag)
{
	long	nbr;
	int		nbr_size;
	char	*result;

	nbr = n;
	nbr_size = get_int_size(nbr);
	if (n < 0)
		nbr = -nbr;
	if (n < 0)
		nbr_size++;
	result = (char *)ft_malloc((nbr_size + 1) * sizeof(char), flag);
	if (!result)
		return (NULL);
	result[nbr_size--] = '\0';
	while (nbr_size >= 0)
	{
		result[nbr_size--] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
