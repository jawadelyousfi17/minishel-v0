/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:47:35 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/17 18:50:56 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*_trim_leading(char *src, char *set, t_token *t)
{
	if (!src)
		return (NULL);
	if (!t || ft_is_op_space(t))
		return (ft_strtrim(src, set, GB_C));
	while (*src && ft_strchr(set, *src))
		src++;
	return (ft_strdup(src, GB_C));
}

char	*_trim_tail(char *src, char *set)
{
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	while (len && ft_strchr(set, src[len - 1]))
		len--;
	return (ft_strndup(src, len, GB_C));
}

int	hande_redirect_expantion(t_token *t, int i, t_minishell *m)
{
	t->type = TEXT;
	if (i == 0)
		t->value = _trim_leading(ft_getenv(t->value + 1, m), " \t", t->next);
	else if (!ft_is_op_space(t->next))
		t->value = _trim_tail(ft_getenv(t->value + 1, m), " \t");
	else
		t->value = ft_getenv(t->value + 1, m);
	if (!t->value)
		return (0);
	return (1);
}
