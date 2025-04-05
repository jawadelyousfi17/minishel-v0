/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:12:35 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:22:00 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_valid_export(char *s)
{
	if (!ft_isalpha(*s) && *s != '_')
		return (0);
	s++;
	if (!*s)
		return (0);
	while (*s && (ft_isalnum(*s) || *s == '_'))
		s++;
	if (!*s)
		return (0);
	if (is_equal(s, "+=") || is_equal(s, "="))
		return (1);
	return (0);
}
