#ifndef GNL_H
# define GNL_H

#include "../include/minishell.h"

char	*ft_str_chr(const char *s, int c);
size_t	ft_str_len(const char *s);
char	*ft_str_dup(const char *s1);
char	*ft_sub_str(char *s, unsigned int start, size_t len);
char	*ft_str_join(char *s1, char *s2);
#endif