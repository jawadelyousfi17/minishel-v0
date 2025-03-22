
#include "gnl.h"

char	*ft_str_chr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (((char *)s + i));
		i++;
	}
	if ((char)c == '\0')
		return (((char *)s + i));
	return (NULL);
}

size_t	ft_str_len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_str_dup(const char *s1)
{
	size_t	i;
	char	*s;

	if (!s1)
		return (NULL);
	i = 0;
	s = malloc(ft_str_len(s1) + 1);
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_sub_str(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (len > ft_str_len(s) - start)
		len = (ft_str_len(s) - start);
	if (ft_str_len(s) < start)
		return (ft_strdup(""));
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_str_join(char *s1, char *s2)
{
	size_t	j;
	size_t	i;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(s2));
	str = malloc(ft_str_len(s1) + ft_str_len(s2) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
