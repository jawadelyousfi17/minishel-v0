/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:12:20 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:22:44 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 0);
	if (!new)
		return (NULL);
	new->value = value;
	new->raw_value = value;
	new->type = type;
	new->is_quoted = 0;
	new->is_ambs = 0;
	new->next = NULL;
	return (new);
}

int	ft_add_token(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = ft_new_token(value, type);
	if (!new)
		return (0);
	if (!*tokens)
	{
		*tokens = new;
		return (1);
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

t_token	*ft_add_token_current(t_token **tokens, t_token *current, t_token *new)
{
	if (!*tokens)
	{
		*tokens = new;
		return (new);
	}
	current->next = new;
	return (new);
}

t_token	*ft_add_token_front(t_token **tokens, char *value, t_token_type type)
{
	t_token	*new;

	new = ft_new_token(value, type);
	if (!new)
		return (NULL);
	new->next = *tokens;
	*tokens = new;
	return (new);
}

t_token	*ft_add_token_after(t_token **head, t_token *node, t_token *new)
{
	if (!new)
		return (NULL);
	if (!node)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		new->next = node->next;
		node->next = new;
	}
	return (new);
}
