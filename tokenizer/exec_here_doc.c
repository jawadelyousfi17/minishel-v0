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
        return 0;
    while (1)
    {
        line = readline("> ");
        if (!line)
            return (close(fd), 1);
        if (is_equal(line, limiter))
        {
            free(line);
            break;
        }
        if (!write_to_heredoc(fd, line, is_qt, m))
            return (close(fd), 0);
        free(line);
    }
    return (close(fd), 1);
}

int ft_execute_heredoc(t_token *t, t_minishell *m)
{
    char *file_path;

    while (t)
    {
        if (t->type == HERE_DOC)
        {
            t->type = HERE_DOC_REDIRECT;
            file_path = create_tmp();
            if (file_path == NULL)
                return 0;
            if (execute_heredoc(file_path, t->next->value, t->is_quoted, m) == 0)
                return (0);
            t->next->value = file_path;
        }
        t = t->next;
    }
    return 1;
}