#include "../include/minishell.h"

// garbage collector struct
// typedef struct s_collect
// {
//     void *content;
//     struct s_collect *next;
// } t_collect;

t_collect *add_back(t_collect *current, t_collect *new)
{
    current->next = new;
    return new;
}

t_collect *new_node(void *ptr)
{
    t_collect *new = malloc(sizeof(t_collect));
    if (!new)
        return NULL;
    new->content = ptr;
    new->next = NULL;
    return new;
}

void *ft_clear(t_collect **head)
{
    t_collect *tmp;
    t_collect *holder;

    holder = *head;
    while (holder)
    {
        tmp = (holder)->next;
        free((holder)->content);
        free(holder);
        holder = tmp;
    }
    *head = NULL;
    return NULL;
}

void *ft_malloc(size_t size, int flag)
{
    static t_collect *current;
    static t_collect *head;
    void *ptr;

    if (flag == 0)
    {
        if (head == NULL)
        {
            ptr = malloc(size);
            if (!ptr)
                return NULL;
            head = new_node(ptr);
            if (!head)
                return ft_clear(&head);
            if (!head->content)
                return NULL;
            current = head;
        }
        else
        {
            current = add_back(current, new_node(malloc(size)));
            if (!current)
                return ft_clear(&head);
        }
        return current->content;
    }
    else if (flag == 2)
        return malloc(size);
    return ft_clear(&head);
}
