/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbouchra <zbouchra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:12:56 by zbouchra          #+#    #+#             */
/*   Updated: 2025/04/05 18:12:57 by zbouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_max_here_docs(t_token *t, t_minishell *m)
{
	int	count;

	count = 0;
	while (t)
	{
		count = 0;
		while (t && t->type != PIPE)
		{
			if (t->type == HERE_DOC)
				count++;
			t = t->next;
		}
		if (count > 16)
		{
			clear_bf_exit(m);
			er4("Error: maximum here-document count exceeded", NULL, NULL,
				NULL);
			exit(2);
		}
		if (t)
			t = t->next;
	}
	return ;
}

t_data	*ft_init_utils(t_token *tokens, t_minishell *m)
{
	t_data	*d;

	if (!ft_expand_vars(&tokens, tokens, m) || !check_ambs(tokens)
		|| !ft_expand_quoted(tokens, m) || !ft_join_tokens(&tokens))
		return (er4("Error: ", strerror(errno), 0, 0), change_exit_code(1, 1),
			NULL);
	d = init_data(tokens);
	if (!d)
		return (er4("Error: ", strerror(errno), 0, 0), change_exit_code(1, 1),
			NULL);
	if (!ft_execute_heredoc(d, m))
		return (ft_close_here_docs(d), change_exit_code(1, 1), NULL);
	return (d);
}

t_data	*ft_initialize_data(char *line, t_minishell *m)
{
	t_token	*tokens;
	char	*err;

	line = ft_strtrim(line, " \t", 0);
	if (!line || ft_strlen(line) == 0)
		return (NULL);
	if (check_unclosed_quotes(line))
		return (er4("unclosed quotes", 0, 0, 0), change_exit_code(258, 1),
			NULL);
	tokens = ft_tokenize_input(line);
	if (!tokens)
		return (er4("Error: ", strerror(errno), 0, 0), change_exit_code(1, 1),
			NULL);
	ft_max_here_docs(tokens, m);
	err = check_syntax_error(tokens);
	if (err != NULL)
		return (er4("syntax error: unexpected token `", err, "'", 0),
			change_exit_code(258, 1), NULL);
	return (ft_init_utils(tokens, m));
}
