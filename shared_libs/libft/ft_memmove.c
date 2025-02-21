/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 20:09:58 by zbouchra          #+#    #+#             */
/*   Updated: 2024/11/12 21:00:03 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;

	if (dst == src)
		return (dst);
	if ((!dst || !src) && len == 0)
		return (dst);
	s = (char *)src;
	d = (char *)dst;
	if (src < dst)
	{
		while (len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
		return (dst);
	}
	else
	{
		return (ft_memcpy(dst, src, len));
	}
}
