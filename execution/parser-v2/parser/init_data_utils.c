#include "../include/minishell.h"

int ft_is_builtin(char *s)
{
    if (s == NULL)
        return 0;
    return is_equal(s, "echo") || is_equal(s, "cd") || is_equal(s, "pwd") || is_equal(s, "export") || is_equal(s, "unset") || is_equal(s, "env") || is_equal(s, "exit");
}

int hl_is_pipe(tt_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (tokens[i]->type == PIPE)
            return 1;
        i++;
    }
    return 0;
}

char **hl_get_cmd(tt_token **start, int pos)
{
    if (pos != UNDIFINED)
        return start[pos]->splited;
    while (*start && (*start)->type != PIPE)
    {
        if ((*start)->type == COMMAND_J)
            return (*start)->splited;
        start++;
    }
    return NULL;
}

int hl_count_files(tt_token **start)
{
    int count;

    count = 0;
    while (*start && (*start)->type != PIPE)
    {
        if ((*start)->type & (REDIRECT_INPUT | REDIRECT_OUTPUT | APPEND | HERE_DOC_REDIRECT))
            count++;
        start++;
    }
    return count;
}

t_list *ft_lst_add(t_list *current, t_list *new)
{
    if (current == NULL || new == NULL)
        return NULL;
    current->next = new;
    return new;
}