#include "../include/minishell.h"

void *ft_perror_putstr(char *s)
{
    if (s == NULL)
        perror("MINISHELL :");
    ft_putstr_fd(ERR_MESSAGE, 2);
    ft_putstr_fd("Syntax Error : ", 2);
    ft_putstr_fd(s, 2);
    ft_putstr_fd("\n", 2);
    return NULL;
}

void *ft_perror(char *s)
{
    perror(s);
    return NULL;
}

t_data *ft_init(char *s, t_minishell *m)
{
    tt_token **tokens;
    char *err;
    t_data *data;

    if (s == NULL || *s == 0)
        return NULL;
    tokens = ft_split_command(s, m);
    if (tokens == NULL)
        return ft_perror(ERR_MESSAGE);
    if(!*tokens)
        return (NULL);
    if (ft_lexing(tokens) == 0)
        return ft_perror(ERR_MESSAGE);
    err = ft_invalid_syntax(tokens);
    if (err)
        return ft_perror_putstr(err);
    
    if (ft_join_cmd(tokens) == 0)
        return ft_perror(ERR_MESSAGE);
    if (ft_execute_heredoc(tokens) == 0)
        return ft_perror(ERR_MESSAGE);
    data = ft_initialize_data(tokens);
    if(data->pipe)
        data->n_of_cmds= ft_lstsize(data->pipe_cmd);
    if (data == NULL)
        return ft_perror(ERR_MESSAGE);
    return data;
}

