#include "../include/minishell.h"

static int hl_count_operators(char **s)
{
    char *operator;

    if (ft_strchr("><|", **s))
    {
        operator=(*s)++;
        while (**s && *operator != '|' && (**s == '<' || **s == '>'))
            (*s)++;
        return 1;
    }
    return 0;
}

static int hl_count_words(char **s)
{
    char quote;

    quote = 0;
    while (**s && !ft_strchr(" \t><|", **s))
    {
        quote = 1;
        if (**s == '"' || **s == '\'')
        {
            quote = *(*s)++;
            while (**s && **s != quote)
                (*s)++;
            if (**s)
                (*s)++;
        }
        else
            while (**s && !ft_strchr(" \t><|'\"", **s))
                (*s)++;
    }
    return quote != 0;
}

int ft_count_tokens(char *s)
{
    int count;
    char qt;

    count = 0;
    while (*s)
    {
        if (hl_skip_white_spaces(&s) == 0)
            break;
        if (hl_count_operators(&s) == 1)
        {
            count++;
            continue;
        }
        count += hl_count_words(&s);
    }
    return count;
}

int ft_count_quoted(char *s)
{
    char quote;
    int counter;

    counter = 0;
    while (*s && !ft_strchr(" \t><|", *s))
    {
        if (*s == '"' || *s == '\'')
        {
            quote = *s++;
            while (*s && *s != quote)
                s++;
            if (*s)
                s++;
            counter++;
        }
        else
        {
            while (*s && !ft_strchr(" \t><|'\"", *s))
                s++;
            counter++;
        }
    }
    return counter;
}
