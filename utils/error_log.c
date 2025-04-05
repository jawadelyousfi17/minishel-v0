/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:10:31 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:10:32 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	er4(char *s1, char *s2, char *s3, char *s4)
{
	char	*r;

	r = ft_strjoin(ERR_MESSAGE, s1, GB_C);
	if (r == NULL)
		return (perror("Error"), -1);
	r = ft_strjoin(r, s2, GB_C);
	if (r == NULL)
		return (perror("Error"), -1);
	r = ft_strjoin(r, s3, GB_C);
	if (r == NULL)
		return (perror("Error"), -1);
	r = ft_strjoin(r, s4, GB_C);
	if (r == NULL)
		return (perror("Error"), -1);
	r = ft_strjoin(r, "\n", GB_C);
	if (r == NULL)
		return (perror("Error"), -1);
	if (write(2, r, ft_strlen(r)) < 0)
		return (perror("Error"), -1);
	return (ft_strlen(r) + 1);
}
