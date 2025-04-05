#include "../include/minishell.h"


t_data *ft_init_utils(t_token *tokens, t_minishell *m)
{
    t_data *d;
    if (!ft_expand_vars(&tokens, tokens, m) || !check_ambs(tokens) 
        || !ft_expand_quoted(tokens, m) ||
        !ft_join_tokens(&tokens))
        return (er4("Error: ", strerror(errno), 0, 0), 
        change_exit_code(1, 1), NULL);
    d = init_data(tokens);
    if (!d)
        return (er4("Error: ", strerror(errno), 0, 0), 
        change_exit_code(1, 1), NULL);
    if (!ft_execute_heredoc(d, m))
        return (ft_close_here_docs(d), change_exit_code(1, 1), NULL);
    return (d);
}

t_data *ft_initialize_data(char *line, t_minishell *m)
{
    t_data *d;
    t_token *tokens;
    char *err;

    line = ft_strtrim(line, " \t", 0);
    if (!line || ft_strlen(line) == 0)
        return NULL;
    if (check_unclosed_quotes(line))
        return (er4("unclosed quotes", 0, 0, 0),
         change_exit_code(258, 1), NULL);
    tokens = ft_tokenize_input(line);
    if (!tokens)
        return (er4("Error: ", strerror(errno), 0, 0),
         change_exit_code(1, 1), NULL);
    err = check_syntax_error(tokens);
    if (err != NULL)
        return (er4("syntax error: unexpected token `", err, "'", 0), 
        change_exit_code(258, 1), NULL);
    return (ft_init_utils(tokens, m));
}
