#include "pipex.h"

char *ft_strdup(const char *s1)
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
