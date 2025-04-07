/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:12:39 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/07 18:08:53 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*genrete_file_name(void)
{
	int		i;
	char	*file_path;
	char	*n;

	i = 0;
	while (1)
	{
		n = ft_itoa(i, GB_C);
		if (n == NULL)
			return (NULL);
		file_path = ft_strjoin("/tmp/.minishel_", n, 0);
		if (file_path == NULL)
			return (NULL);
		if (access(file_path, F_OK) != 0)
			return (file_path);
		i++;
	}
	return (NULL);
}

int	change_exit_code(int e_code, int flag)
{
	static int	exit_code;

	if (flag)
		exit_code = e_code;
	return (exit_code);
}

char	*ft_getenv(char *name, t_minishell *m)
{
	char	*value;
	char	*var_val;

	if (is_equal(name, "?"))
	{
		var_val = ft_itoa(change_exit_code(0, !m->is_first_pipe), GB_C);
		if (!var_val)
			return (NULL);
		return (var_val);
	}
	value = gb_get_env(*(m->env), name);
	if (!value)
		return (ft_strdup("", GB_C));
	var_val = ft_strdup(value, GB_C);
	free(value);
	if (!var_val)
		return (NULL);
	return (var_val);
}

int	ft_is_operator(t_token *token)
{
	if (token->type == PIPE || token->type == REDIRECT_INPUT
		|| token->type == REDIRECT_OUTPUT || token->type == APPEND
		|| token->type == HERE_DOC)
		return (1);
	return (0);
}

int	ft_is_op_space(t_token *t)
{
	return (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT
		|| t->type == APPEND || t->type == PIPE || t->type == SPACES
		|| t->type == HERE_DOC);
}
