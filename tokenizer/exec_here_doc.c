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
        file_path = ft_strjoin("minishel_", n, 0);
        if (file_path == NULL)
            return NULL;
        if (access(file_path, F_OK) != 0)
            return file_path;
        i++;
    }
    return (NULL);
}

static int write_to_heredoc(int fd, char *line, int is_qt, t_minishell *m)
{
    char *r;

    if (!is_qt)
    {
        r = ft_expand_here_doc(line, m);
        if (r == NULL)
            return (free(line), 0);
    }
    else
        r = line;
    if (write(fd, r, ft_strlen(r)) == -1 || write(fd, "\n", 1) == -1)
        return (free(line), 0);
    return 1;
}

static int execute_heredoc(char *file_path, char *limiter, int is_qt, t_minishell *m)
{
    char *line;
    int fd;

    fd = open(file_path, O_CREAT | O_RDWR, 0644);
    if (fd < 0)
        return fd;
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
        if (!write_to_heredoc(fd, line, is_qt, m))
            return (unlink(file_path), -1);
        free(line);
    }
    return (unlink(file_path), fd);
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
            printf("is quoted %d\n", f[i]->is_quoted);
            fd = execute_heredoc(file_path, f[i]->file, f[i]->is_quoted, m);
            if (fd < 0)
            {
                return 0;
            }
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
