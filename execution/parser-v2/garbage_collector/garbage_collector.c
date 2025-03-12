#include "../include/minishell.h"

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

    if (flag == GB)
    {
        if (head == NULL)
        {
            head = new_node(malloc(size));
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
    else if (flag == NO_GB)
        return malloc(size);
    return ft_clear(&head);
}

// DRAFT
// void *ft_malloc_2(size_t size, int flag)
// {
//     static int index;
//     static int max_size ;
//     static void **collect;
//     void **new_collect;
//     int i;

//     if (!collect)
//     {
//         index = 0;
//         max_size = 2560000;
//         collect = malloc(max_size * sizeof(void *));
//         if (!collect)
//             return NULL;
//     }

//     if (flag == 0)
//     {
//         if (index == max_size)
//         {
//             max_size *= 2;  // Double the size to minimize realloc calls
//             new_collect = realloc(collect, max_size * sizeof(void *));
//             if (!new_collect)
//                 return NULL;  // Keep the original memory on realloc failure
//             collect = new_collect;

//         }

//         collect[index] = malloc(size);
//         if (!collect[index])
//             return NULL;

//         return collect[index++];
//     }

//     for (i = 0; i < index; i++)
//         free(collect[i]);

//     free(collect);
//     collect = NULL;
//     index = 0;  // Reset index after freeing

//     return NULL;
// }
