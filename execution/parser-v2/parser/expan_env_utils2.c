#include "../include/minishell.h"

int ft_is_valid_start(char c)
{
    return (ft_isalpha(c) || c == '_' || c == '?' || c == '"' || c == '\'');
}

int ft_is_valid_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

int add_to_list(t_list **head, char *content)
{
    return ft_lstadd_back(head, ft_lstnew(content));
}