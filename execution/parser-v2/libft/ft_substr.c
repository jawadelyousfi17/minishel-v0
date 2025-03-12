/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:40:40 by jel-yous          #+#    #+#             */
/*   Updated: 2024/11/04 12:21:39 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, int flag)
{
	size_t		index;
	char		*substring;

	static int t;
	t++;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", flag));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s) - start;
	index = 0;
	substring = (char *)ft_malloc((len + 1) * sizeof(char), flag);
	if (!substring)
		return (NULL);
	while (s[start] && index < len)
		substring[index++] = s[start++];
	substring[index] = '\0';
	return (substring);
}
