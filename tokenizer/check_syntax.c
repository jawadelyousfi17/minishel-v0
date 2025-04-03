#include "../include/minishell.h"

int check_unclosed_quotes(char *s)
{
    char quote_type;

    while (*s)
    {
        if (*s == DOUBLE_QUOTE || *s == SINGLE_QUOTE)
        {
            quote_type = *s;
            s++;
            while (*s && *s != quote_type)
                s++;
            if (!*s)
                return (1);
            else
                s++;
        }
        else
            s++;
    }
    return (0);
}

char *check_redir_syntax(t_token **tk)
{
    t_token *t;

    t = *tk;
    t = t->next;
    if (!t)
        return ("newline");
    while (t && t->type == SPACES)
        t = t->next;
    if (!t)
        return ("newline");
    if (t->type == PIPE || t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND || t->type == HERE_DOC)
        return (t->value);
    *tk = t;
    return (NULL);
}

char *check_pipe_syntax(t_token **tk)
{
    t_token *t;

    t = *tk;
    t = t->next;
    if (!t)
        return ("newline");
    while (t && t->type == SPACES)
        t = t->next;
    if (!t)
        return ("newline");
    if (t->type == PIPE)
        return (t->value);
    return (NULL);
}

char *check_syntax_error(t_token *t)
{
    char *err;

    while (t && t->type == SPACES)
        t = t->next;
    if (t->type == PIPE)
        return (t->value);
    while (t)
    {
        if (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND || t->type == HERE_DOC)
        {
            err = check_redir_syntax(&t);
            if (err)
                return (err);
        }
        else if (t->type == PIPE)
        {
           err = check_pipe_syntax(&t);
              if (err)
                return (err);
        }
        t = t->next;
    }
    return (NULL);
}
