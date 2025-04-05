/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:49:36 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 19:00:41 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_start_with(char *src, char *target)
{
	size_t	len;
	size_t	i;

	i = 0;
	if (ft_strlen(target) > ft_strlen(src))
		return (0);
	while (target[i])
	{
		if (target[i] != src[i])
			return (0);
		i++;
	}
	return (1);
}
