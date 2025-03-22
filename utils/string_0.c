#include "utils.h"

size_t ft_strlen(const char *s)
{
    const char *current = s;

    if (!s)
        return 0;

    while (*current)
        current++;

    return current - s;
}

char	*ft_strjoin(const char *s1, const char *s2, int flag)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*joined;

	len2 = ft_strlen(s2);
	len1 = ft_strlen(s1);
	i = 0;
	j = 0;
	joined = (char *)ft_malloc(len1 + len2 + 1, flag);
	if (!joined)
		return (NULL);
	while (i < len1)
	{
		joined[i] = s1[i];
		i++;
	}
	while (j < len2)
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}



int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	size_t			i;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (t1[i] && t2[i] && t1[i] == t2[i] && i < n)
		i++;
	if (i < n)
		return (t1[i] - t2[i]);
	return (0);
};
