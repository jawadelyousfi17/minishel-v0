#include "../include/minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	if (content == NULL)
		return NULL;
	new_node = (t_list *)ft_malloc(sizeof(t_list), 0);
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return 0;
	if (!*lst)
	{
		*lst = new;
		return 1;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return 1;
}

char *ft_join_list(t_list *t)
{
   char *r;

    r = NULL;
    while (t)
    {
        r = ft_strjoin(r, (char *)t->content, GB_C);
        if (!r)
            return NULL;
        t = t->next;
    }
    return r;
}

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		size;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}