#include "utils.h"

char	*ft_strdup(const char *s, int flag)
{
	size_t		size;
	size_t		index;
	char		*new_s;

	size = ft_strlen(s);
	new_s = (char *)ft_malloc((sizeof(char) * (size + 1)), flag);
	if (!new_s)
		return (NULL);
	index = 0;
	while (index < size)
	{
		new_s[index] = s[index];
		index++;
	}
	new_s[index] = '\0';
	return (new_s);
}

static int	is_char_set(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, int flag)
{
	size_t		index;
	char		*substring;

	static int t;
	t++;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("", flag));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s) - start;
	index = 0;
	substring = (char *)ft_malloc((len + 1) * sizeof(char), flag);
	if (!substring)
		return (NULL);
	while (s[start] && index < len)
		substring[index++] = s[start++];
	substring[index] = '\0';
	return (substring);
}

char	*ft_strtrim(char const *s1, char const *set, int flag)
{
	size_t	start;
	size_t	index;
	size_t	s1_len;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	if (!*set)
		return (ft_strdup(s1, flag));
	s1_len = ft_strlen(s1);
	index = 0;
	while (s1[index] && is_char_set(s1[index], set))
		index++;
	if (index == s1_len)
		return (ft_strdup("", flag));
	start = index;
	index = s1_len - 1;
	while (is_char_set(s1[index], set))
		index--;
	return (ft_substr(s1, start, index - start + 1, flag));
}

char	*ft_strchr(const char *s, int c)
{
	char	*t;

	if (!s)
		return (NULL);
	t = (char *)s;
	c = (char) c;
	while (*t)
	{
		if (*t == c)
			return (t);
		t++;
	}
	if (!*t && !c)
		return (t);
	return (NULL);
}




