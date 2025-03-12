/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:52:46 by jel-yous          #+#    #+#             */
/*   Updated: 2025/03/11 22:13:23 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	if (!s || !*s)
		return (NULL);
	t = (char *)s;
	c = (char) c;
	while (*t)
	{
		if (*t == c)
			return (t);
		t++;
	}
	if (!*t && !c)
		return (t);
	return (NULL);
}
