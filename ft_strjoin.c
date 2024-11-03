#include "pipex.h"

static char *ft_strdup(const char *s1)
{
	char *dest;
	char *p;
	int len;

	len = 0;
	while (s1[len])
		len++;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	p = dest;
	while (*s1)
		*p++ = *s1++;
	*p = '\0';
	return (dest);
}

static char *join_string(char *ptr, char const *s1, char const *s2)
{
	size_t i;
	size_t j;

	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i + j] = s2[j];
		++j;
	}
	ptr[i + j] = '\0';
	return (ptr);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	char *ptr;
	size_t len1;
	size_t len2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!ptr)
		return (0);
	ptr = join_string(ptr, s1, s2);
	return (ptr);
}
