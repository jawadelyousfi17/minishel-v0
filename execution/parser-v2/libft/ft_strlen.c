/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:58:56 by jel-yous          #+#    #+#             */
/*   Updated: 2024/12/30 20:40:52 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen(const char *s)
{
    const char *current = s;

    if (!s)
        return 0;

    while (*current)
        current++;

    return current - s;  // Return the length as the difference between the end and start
}
