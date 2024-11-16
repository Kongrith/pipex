/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khkomasa <khkomasa@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:10:36 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 15:10:45 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	length;
	size_t	index;

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
