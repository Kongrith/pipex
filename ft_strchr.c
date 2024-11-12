#include "pipex.h"

char *ft_strchr(const char *s, int c)
{
	char *ptr;

	c = c % 256;
	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == c)
			return (ptr);
		++ptr;
	}
	if (c == '\0')
		return (ptr);
	return (NULL);
}
