/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:12:59 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:31:23 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_files	*ft_ifl(t_token *t, t_token_type type, int is_ambs,
		int is_quoted)
{
	t_files	*f;

	f = ft_malloc(sizeof(t_files), GB_C);
	if (!f)
		return (NULL);
	f->redirect_type = type;
	f->file = t->next->value;
	f->is_ambs = is_ambs;
	f->is_quoted = is_quoted;
	f->fd = -1;
	if (f->is_ambs)
		f->file = t->value;
	return (f);
}

int	process_tokens(t_token **t, t_list **c, t_list **f)
{
	t_list	*n;
	t_files	*files;

	while (*t && (*t)->type != PIPE)
	{
		if ((*t)->type == TEXT)
		{
			n = ft_lstnew((*t)->value);
			if (!n)
				return (0);
			ft_lstadd_back(c, n);
		}
		else if ((*t)->type == REDIRECT_INPUT || (*t)->type == REDIRECT_OUTPUT
			|| (*t)->type == APPEND || (*t)->type == HERE_DOC)
		{
			files = ft_ifl(*t, (*t)->type, (*t)->is_ambs, (*t)->is_quoted);
			n = ft_lstnew(files);
			if (!files || !n)
				return (0);
			ft_lstadd_back(f, n);
			*t = (*t)->next;
		}
		*t = (*t)->next;
	}
	return (1);
}

t_data	*init_no_pipe(t_token **tk)
{
	t_token	*t;
	t_data	*d;
	t_list	*f;
	t_list	*c;

	(1) && (c = NULL, f = NULL, t = *tk);
	d = ft_malloc(sizeof(t_data), GB_C);
	if (!d)
		return (NULL);
	d->pipe = 0;
	if (!process_tokens(&t, &c, &f))
		return (NULL);
	d->_t_cmd = c;
	d->_t_files = f;
	d->files = ft_list_to_files(f);
	d->cmd = ft_list_to_array(c);
	d->n_of_cmds = c != NULL;
	d->is_builtin = 0;
	if (d->cmd)
		d->is_builtin = ft_is_builtin(d->cmd[0]);
	*tk = t;
	return (d);
}

t_list	*init_pipes(t_token **tk)
{
	t_token	*t;
	t_list	*p;
	t_data	*d;
	t_list	*n;

	p = NULL;
	t = *tk;
	while (t)
	{
		d = init_no_pipe(&t);
		if (!d)
			return (NULL);
		n = ft_lstnew(d);
		if (!n)
			return (NULL);
		ft_lstadd_back(&p, n);
		if (t)
			t = t->next;
	}
	return (p);
}

t_data	*init_data(t_token *t)
{
	t_data	*d;
	int		count_pipe;

	count_pipe = ft_count_token(t, PIPE);
	if (count_pipe == 0)
	{
		d = init_no_pipe(&t);
		if (!d)
			return (NULL);
		d->pipe = 0;
		return (d);
	}
	d = ft_malloc(sizeof(t_data), GB_C);
	if (!d)
		return (NULL);
	d->pipe = 1;
	d->pipe_cmd = init_pipes(&t);
	if (!d->pipe_cmd)
		return (NULL);
	d->n_of_cmds = ft_lstsize(d->pipe_cmd);
	return (d);
}
