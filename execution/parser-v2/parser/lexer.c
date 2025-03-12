#include "../include/minishell.h"

t_tokens hl_tokenizer(tt_token *token, tt_token *prev)
{
    if (token->type == OPERATOR)
    {
        if (is_equal(token->value, "<"))
            return REDIRECT_INPUT;
        if (is_equal(token->value, ">"))
            return REDIRECT_OUTPUT;
        if (is_equal(token->value, ">>"))
            return APPEND;
        if (is_equal(token->value, "<<"))
            return HERE_DOC;
        if (is_equal(token->value, "|"))
            return PIPE;
        return ERROR_TOKEN;
    }
    if (prev && is_redirection(prev->type) && prev->type != HERE_DOC)
        return FILE_T;
    if (prev && prev->type == HERE_DOC)
        return LIMITER;
    return COMMAND;
}

char **hl_join_cmd(tt_token **start, tt_token **end, int count)
{
    char **r;

    if (count == 0)
        return (char **)0x1;
    r = ft_malloc(sizeof(char *) * (count + 1), 0);
    if (r == NULL)
        return NULL;
    while (start < end)
    {
        if ((*start)->type == COMMAND)
        {
            *r++ = (*start)->value;
            if (count != 0)
            {
                count = 0;
                (*start)->type = COMMAND_J;
                (*start)->splited = r - 1;
            }
        }
        start++;
    }
    *r = NULL;
    return r;
}

int ft_join_cmd(tt_token **token)
{
    int count;
    tt_token **tmp;

    while (*token)
    {
        tmp = token;
        count = 0;
        while (*token && (*token)->type != PIPE)
        {
            if ((*token)->type == COMMAND)
                count++;
            token++;
        }
        if (count != 0 && hl_join_cmd(tmp, token, count) == NULL)
            return 0;
        if (*token)
            token++;
    }
    return 1;
}

char *ft_invalid_syntax(tt_token **tokens)
{
    int i = 0;
    if (!tokens || !*tokens)
        return 0;
    if (tokens[i]->type == PIPE)
        return tokens[i]->value;
    while (tokens[i])
    {
        if (tokens[i]->type == ERROR_TOKEN)
            return tokens[i]->value;
        if (tokens[i]->type == PIPE && tokens[i + 1] && !(tokens[i + 1]->type & VALID_AFTER_PIPE))
            return tokens[i + 1]->value;
        if (is_redirection(tokens[i]->type) && (!tokens[i + 1] || !(tokens[i + 1]->type & VALID_AFTER_REDIRECTION)))
        {
            if (tokens[i + 1])
                return tokens[i + 1]->value;
            else
                return "newline";
        }
        i++;
    }
    return NULL;
}

int ft_lexing(tt_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (i > 0)
            tokens[i]->type = hl_tokenizer(tokens[i], tokens[i - 1]);
        else
            tokens[i]->type = hl_tokenizer(tokens[i], NULL);
        i++;
    }
    return 1;
}