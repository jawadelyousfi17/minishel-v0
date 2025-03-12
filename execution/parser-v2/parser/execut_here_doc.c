#include "../include/minishell.h"

static char *create_tmp()
{
    int i;
    char *file_path;
    char *n;

    i = 0;
    while (1)
    {
        n = ft_itoa(i);
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

static int execute_heredoc(char *file_path, char *limiter)
{
    char *tmp;
    int fd;

    fd = open(file_path, O_CREAT | O_RDWR , S_IRUSR | S_IWUSR, 0644);
    if (fd < 0)
        return 0;
    while (1)
    {
        tmp = readline("HERE DOC > ");
        if (!tmp)
            return (close(fd), 0);
        if (tmp && is_equal(tmp, limiter))
        {
            free(tmp);
            break;
        }
        if (write(fd, tmp, ft_strlen(tmp)) == -1 || write(fd, "\n", 1) == -1)
            return (close(fd), free(tmp), 0);
        free(tmp);
    }
    close(fd);
    return 1;
}

int ft_execute_heredoc(tt_token **tokens)
{
    char *file_path;
    t_token *data;
    int i;

    i = 0;
    file_path = NULL;
    while (tokens[i])
    {
        if (tokens[i]->type == HERE_DOC)
        {
            tokens[i]->type = HERE_DOC_REDIRECT;
            file_path = create_tmp();
            if (file_path == NULL)
                return 0;
            if (execute_heredoc(file_path, tokens[i + 1]->value) == 0)
                return (0);
            tokens[++i]->type = FILE_T;
            tokens[i]->value = file_path;
        }
        i++;
    }
    return 1;
}
