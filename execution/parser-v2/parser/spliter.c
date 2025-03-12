#include "../include/minishell.h"

static tt_token *hl_extract_token(char **s)
{
    tt_token *token;
    char *start;

    start = (*s)++;
    while (**s && *start != '|' && (**s == '<' || **s == '>') )
        (*s)++;
    token = ft_malloc(sizeof(tt_token), 0);
    if (token == NULL)
        return NULL;
    token->type = OPERATOR;
    token->value = ft_strndup(start, *s - start, 0);
    if (token->value == NULL)
        return NULL;
    return token;
}

static tt_token *hl_malloc_token(char *s)
{
    char **quoted_tokens;
    tt_token *token;
    int i;
    int size;

    token =  ft_malloc(sizeof(tt_token), 0);
    if (token == NULL)
        return NULL;
    i = 0;
    size = ft_count_quoted(s) + 1;
    token->type = STRING;
    quoted_tokens = ft_malloc(sizeof(char *) * size, 0);
    if (quoted_tokens == NULL)
        return NULL;
    while (i < size)
        quoted_tokens[i++] = NULL;
    token->splited = quoted_tokens;
    return token;
}

// extract the words from the string
// return NULL in case of malloc failure
static tt_token *hl_extract_words(char **s, t_minishell *m)
{
    tt_token *token;
    int j;
    char *start;

    token = hl_malloc_token(*s);
    if (token == NULL)
        return NULL;
    j = 0;
    while (**s && !ft_strchr(" \t><|", **s))
    {
        start = *s;
        if ((**s == '"' || **s == '\'') && (*s)++)
        {
            while (**s && **s != *start)
                (*s)++;
            (*s) += **s != 0;
        }
        else
            while (**s && !ft_strchr(" \t><|'\"", **s))
                (*s)++;
        token->splited[j] =  ft_expanding(ft_strndup(start, *s - start, 0), m);
        if (token->splited[j++] == NULL)
            return NULL;
    }
    return token;
}


static tt_token **hl_malloc_tokens(char *s)
{
    tt_token **tokens;
    int size;
    int i;

    i = 0;
    size = ft_count_tokens(s) + 1;
    tokens =  ft_malloc(sizeof(tt_token *) * size, 0);
    if (tokens == NULL)
        return NULL;
    while (i < size)
        tokens[i++] = NULL;
    return tokens;
}


char *hl_join_arr(char **arr)
{
    char *result;
    size_t i;
    size_t len;
    
    i = 0;
    len = 0;
    while (arr[i])
       len += ft_strlen(arr[i++]);
    result = ft_malloc(len + 1, 0);
    if (!result)
        return NULL;
    i = 0;
    *result = 0;
    while (arr[i])
    {
        ft_strlcat(result, arr[i], len + 1);
        i++;
    }
    return result;
}

void *hl_extract_join(tt_token **tokens, int index, char **s, t_minishell *m)
{
    tokens[index] = hl_extract_words(s, m);
    if (tokens[index] == NULL)
        return NULL;
    tokens[index]->value = hl_join_arr(tokens[index]->splited);
    if (tokens[index]->value == NULL)
        return NULL;
    return (void *)0x1;
}

tt_token **ft_split_command(char *s, t_minishell *m)
{
    tt_token **tokens;
    int index;

    (1) && (tokens = hl_malloc_tokens(s), index = 0);
    if (tokens == NULL)
        return NULL;
    while (*s)
    {
        if (hl_skip_white_spaces(&s) == 0)
            break;
        if (*s && ft_strchr("><|", *s))
        {
            tokens[index] = hl_extract_token(&s);
            if (tokens[index++] == NULL)
                return NULL;
        }
        else if (*s && !ft_strchr(" \t><|", *s))
        {
           if (hl_extract_join(tokens, index++, &s, m) == NULL)
               return NULL;
        }
    }
    return tokens;
}

