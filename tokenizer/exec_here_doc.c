#include "../include/minishell.h"

static char *create_tmp()
{
    int i;
    char *file_path;
    char *n;

    i = 0;
    while (1)
    {
        n = ft_itoa(i, GB_C);
        if (n == NULL)
            return NULL;
        file_path = ft_strjoin("/tmp/minishel_", n, 0);
        if (file_path == NULL)
            return NULL;
        if (access(file_path, F_OK) != 0)
            return file_path;
        i++;
    }
    return (NULL);
}

static void read_line(char *limiter, int is_qt, t_minishell *m, char **r)
{
    char *line;
    char *nl;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (is_equal(line, limiter))
        {
            free(line);
            break;
        }
        nl = ft_strjoin(line, "\n", 0);
        free(line);
        if (!is_qt)
            nl = ft_expand_here_doc(nl, m);
        *r = ft_strjoin(*r, nl, 0);
        if (*r == NULL || nl == NULL)
            return ;
    }
    if (!*r)
        *r = ft_strdup("", 0);
}

static int execute_heredoc(char *file_path, char *limiter, int is_qt, t_minishell *m)
{
    int fd;
    char *r;

    r = NULL;
    read_line(limiter, is_qt, m, &r);
    if (r == NULL)
        return -1;
    fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0)
        return -1;
    if (write(fd, r, ft_strlen(r)) < 0)
        return -1;
    close(fd);
    fd = open(file_path, O_RDONLY);
    if (unlink(file_path) < 0)
        return -1;
    return fd;
}

int ft_execute_files(t_files **f, t_minishell *m)
{
    int fd;
    int i;
    char *file_path;

    i = 0;
    if (!f)
        return 1;
    while (f[i])
    {
        if (f[i]->redirect_type == HERE_DOC)
        {
            file_path = create_tmp();
            if (file_path == NULL)
                return 0;
            fd = execute_heredoc(file_path, f[i]->file, f[i]->is_quoted, m);
            if (fd < 0)
                return 0;
            f[i]->fd = fd;
        }
        i++;
    }
    return 1;
}

int ft_execute_heredoc(t_data *d, t_minishell *m)
{
    char *file_path;
    int fd;
    t_list *d1;
    if (d->pipe)
    {
        d1 = d->pipe_cmd;
        while (d1)
        {
            if (ft_execute_files(((t_data *)d1->content)->files, m) == 0)
                return 0;
            d1 = d1->next;
        }
    }
    else
    {
        if (ft_execute_files(d->files, m) == 0)
            return 0;
    }
    return 1;
}
