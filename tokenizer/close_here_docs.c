#include "../include/minishell.h"

static int ft_close_hd_utils(t_files **f)
{
    int i;

    if (!f)
        return (1);
    i = 0;
    while (f[i])
    {
        if (f[i]->redirect_type == HERE_DOC && f[i]->fd > 0)
        {
            if (close(f[i]->fd) == -1)
                return (0);
        }
        i++;
    }
    return (1);
}

int ft_close_here_docs(t_data *d)
{
    t_data *tmp_data;
    t_list *t;
    int i;

    i = 0;
    if (d->pipe)
    {
        t = d->pipe_cmd;
        while (t)
        {
            ft_close_here_docs((t_data *)t->content);
            t = t->next;
        }
    }
    else
    {
        if (!ft_close_hd_utils(d->files))
        {
            er4("Error: ", strerror(errno), NULL, NULL);
            return (0);
        }
    }
    return (1);
}
