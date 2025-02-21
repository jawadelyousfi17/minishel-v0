/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:41:52 by zbouchra          #+#    #+#             */
/*   Updated: 2024/11/13 13:38:04 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	sl;
	size_t	dl;

	if (dstsize == 0)
		return (ft_strlen(src));
	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	i = 0;
	if (dl >= dstsize)
		return (dstsize + sl);
	while (src[i] && i < dstsize - dl - 1)
	{
		dst[i + dl] = src[i];
		i++;
	}
	if ((dl + i) < dstsize)
		dst[i + dl] = '\0';
	return (sl + dl);
}
