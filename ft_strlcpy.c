#include "pipex.h"

size_t ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t length;
	size_t index;

	length = ft_strlen((char *)src);
	index = 0;
	if (size == 0)
		return (length);
	while (index < size - 1 && index < length)
	{
		*(dst + index) = *(src + index);
		++index;
	}
	*(dst + index) = '\0';
	while (src[index] != '\0')
		++index;
	return (index);
}
