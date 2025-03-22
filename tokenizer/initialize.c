#include "../include/minishell.h"

t_data *ft_initialize_data(char *line, t_minishell *m)
{
    t_data *d;
    t_token *tokens;
    char *err;

    line = ft_strtrim(line, " \t", 0);
    if (!line || ft_strlen(line) == 0)
        return NULL;
    if (check_unclosed_quotes(line))
        return (er4("unclosed quotes", 0, 0, 0), NULL);
    tokens = ft_tokenize_input(line);
    if (!tokens)
        return (er4("Memory allocation error", 0, 0, 0), NULL);
    err = check_syntax_error(tokens);
    if (err != NULL)
        return (er4("syntax error: unexpected token `", err, "'", 0), NULL);
    if (!ft_expand_vars(&tokens, tokens, m) || !check_ambs(tokens) || !ft_expand_quoted(tokens, m) ||
        !ft_join_tokens(&tokens) || !ft_execute_heredoc(tokens, m))
        return (er4("Memory allocation error", 0, 0, 0), NULL);
    d = init_data(tokens);
    if (!d)
        return (er4("Memory allocation error", 0, 0, 0), NULL);
    return (d);
}
