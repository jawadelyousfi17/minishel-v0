#include "../include/minishell.h"

t_token *ft_new_util(char **s)
{
	t_token *new;

	if (**s == ' ' || **s == '\t')
		new = ft_tokenize_space(s);
	else if (**s == DOUBLE_QUOTE)
		new = ft_tokenize_dquote(s);
	else if (**s == SINGLE_QUOTE)
		new = ft_tokenize_squote(s);
	else if (**s == '|')
		new = ft_tokenize_pipe(s);
	else if (**s == '<')
		new = ft_tokenize_redir_in(s);
	else if (**s == '>')
		new = ft_tokenize_redir_out(s);
	else if (**s == '$')
		new = ft_tokenize_variable(s);
	else
		new = ft_tokenize_txt(s);
	return (new);
}

t_token *ft_tokenize_input(char *s)
{
	t_token *tokens;
	t_token *current;
	t_token *new;

	tokens = NULL;
	while (*s)
	{
		new = ft_new_util(&s);
		if (!new)
			return (NULL);
		current = ft_add_token_current(&tokens, current, new);
	}
	return (tokens);
}
