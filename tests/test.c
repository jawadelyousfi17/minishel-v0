#include "../include/minishell.h"
#include <time.h>

// Text Colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

char *_trs(t_token_type t)
{
    if (t == TEXT)
        return "TEXT";
    if (t == S_QUOTE)
        return "S_QUOTE";
    if (t == D_QUOTE)
        return "D_QUOTE";
    if (t == VAR)
        return "VAR";
    if (t == EXPAND)
        return "EXPAND";
    if (t == PIPE)
        return "PIPE";
    if (t == REDIRECT_INPUT)
        return "REDIRECT_INPUT";
    if (t == REDIRECT_OUTPUT)
        return "REDIRECT_OUTPUT";
    if (t == HERE_DOC)
        return "HERE_DOC";
    if (t == APPEND)
        return "APPEND";
    if (t == SPACES)
        return "SPACES";
    return "UNKNOWN";
}

void _print_tokens(t_token *tokens)
{
    printf(CYAN "\n" RESET);
    while (tokens)
    {
        printf("value: " GREEN "{%s}" RESET "\ntype:" GREEN " %s" RESET, tokens->value, _trs(tokens->type));
        if (tokens->type == HERE_DOC)
            printf(BLUE "\nis_quoted: %d" RESET, tokens->is_quoted);
        if (tokens->type == REDIRECT_INPUT || tokens->type == REDIRECT_OUTPUT || tokens->type == APPEND)
            printf(BLUE "\nis_ambs: %d" RESET, tokens->is_ambs);
        printf("\n\n");
        tokens = tokens->next;
    }
    printf("\n\n");
}

void _print_data(t_data *d)
{
    {
        if (!d->pipe)
        {
            if (d->files)
            {
                int i = 0;
                while (d->files[i])
                {
                    t_files *file = d->files[i];
                    printf("file: "
                           "%s"
                           "\ntype: "
                           "%s"
                           "\nis_ambs: "
                           "%s"
                           "\n",
                           file->file, _trs(file->redirect_type), file->is_ambs ? "true" : "false");
                        i++;
                }
                // printf("\n");
            }
            else
            {
                printf("No files\n");
            }
            if (d->cmd)
            {
                int i = 0;
                printf("cmds: ");
                while (d->cmd[i])
                {
                    printf("{%s} ", d->cmd[i]);
                    i++;
                }
                printf("\n");
            }
            else
            {
                printf("No cmds\n");
            }
            return;
        }
    }
    t_list *p = d->pipe_cmd;
    printf("pipes: \n");
    while (p)
    {
        t_data *d = p->content;
        _print_data(d);
        p = p->next;
        printf("\n");
    }
}

int main(int argc, char **argv, char **env)
{

    char **new_env = gb_get_all_env(env); // check env -i
    t_minishell *m = malloc(sizeof(t_minishell));
    m->env = &new_env;
    m->exit_code = 0;
    m->cwd = getcwd(NULL, 0);
    if (argc != 2)
    {
        printf("Usage: %s <command>\n", argv[0]);
        return 1;
    }

    

    char *line = argv[1];
    t_data *d = ft_initialize_data(line, m);
    if (!d)
    {
        return 1;
    }
    _print_data(d);
    ft_malloc(1, GB_CLEAR);
}
