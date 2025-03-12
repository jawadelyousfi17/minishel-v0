#include "../include/minishell.h"



t_files **hl_get_files(tt_token **start, int count)
{
    t_files **files;
    int i;

    i = 0;
    if (count == UNDIFINED)
        count = hl_count_files(start);
    if (count == 0)
        return NULL;
    files = ft_malloc(sizeof(t_files *) * (count + 1), 0);
    if (files == NULL)
        return (void *)ERR_MALLOC;
    while (*start && (*start)->type != PIPE)
    {
        if ((*start)->type & (REDIRECT_INPUT | REDIRECT_OUTPUT | APPEND | HERE_DOC_REDIRECT))
        {
            files[i] =   ft_malloc(sizeof(t_files), 0);
            if (files[i] == NULL)
                return (void *)ERR_MALLOC;
            files[i]->type = (*start++)->type;
            files[i++]->file = (*start)->value;
        }
        start++;
    }
    files[i] = NULL;
    return files;
}

t_data *hl_init_data(tt_token **start, int pos, int count)
{
    t_data *data;

    data = ft_malloc(sizeof(t_data), 0);
    if (data == NULL)
        return NULL;
    data->cmd = hl_get_cmd(start, pos);
    data->is_builtin = 0;
    if (data->cmd != NULL)
        data->is_builtin = ft_is_builtin(data->cmd[0]);
    data->files = hl_get_files(start, count);
    if (data->files == (void *)ERR_MALLOC)
        return NULL;
    if (count == UNDIFINED)
        data->pipe = 0;
    else
        data->pipe = 1;
    return data;
}


void *hl_create_pipe(t_list **pipes, t_list **current, tt_token **start, int count)
{
    if (*pipes == NULL)
    {
        *pipes = ft_lstnew(hl_init_data(start, UNDIFINED, count));
        if (*pipes == NULL)
            return NULL;
    }
    else
    {
        *current = ft_lst_add(*current, ft_lstnew(hl_init_data(start, UNDIFINED, count)));
        if (*current == NULL)
            return NULL;
    }
    if (*current == NULL)
        *current = *pipes;
    return (void *)0x1;
}

t_list *hl_create_pipe_list(tt_token **tokens)
{
    t_list *pipes;
    t_list *current;
    tt_token **start;
    int count;

    (1) && (pipes = NULL, current = NULL);
    while (*tokens)
    {
        (1) && (count = 0, start = tokens);
        while (*tokens && (*tokens)->type != PIPE)
            count += ((*tokens++)->type & (REDIRECT_INPUT | REDIRECT_OUTPUT | APPEND | HERE_DOC_REDIRECT)) != 0;
        if (hl_create_pipe(&pipes, &current, start, count) == NULL)
            return NULL;
        if (*tokens)
            tokens++;
    }
    return pipes;
}

t_data *ft_initialize_data(tt_token **tokens)
{
    t_data *data;

    if (hl_is_pipe(tokens) == 0)
        return hl_init_data(tokens, UNDIFINED, UNDIFINED);
    data =  ft_malloc(sizeof(t_data), 0);
    if (data == NULL)
        return NULL;
    data->pipe = 1;
    data->pipe_cmd = hl_create_pipe_list(tokens);
    if (data->pipe_cmd == NULL)
        return NULL;
    return data;
}

int ft_cound_pipes(t_data *data)
{
    t_list *pipes;

    if (data->pipe == 0)
        return 0;
    pipes = data->pipe_cmd;
    return ft_lstsize(pipes);
}
