/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khkomasa <khkomasa@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:44:39 by khkomasa          #+#    #+#             */
/*   Updated: 2024/11/16 14:19:59 by khkomasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_is_delimiter(char c, char delim)
{
	return (c == '\n' || c == '\t' || c == delim);
}

static int	ft_words_len(char *str, char delim)
{
	int	idx;
	int	length;

	idx = 0;
	length = 0;
	while (str[idx] != '\0')
	{
		if (!ft_is_delimiter(str[idx], delim))
		{
			length++;
			idx++;
		}
		else
			idx++;
	}
	return (length);
}

static	char	*ft_get_word(char *str, char delim)
{
	int		idx;
	char	*word;

	idx = 0;
	while (str[idx] != '\0' && !ft_is_delimiter(str[idx], delim))
		idx++;
	word = (char *)malloc(sizeof(char) * (idx + 1));
	if (!word)
		return (NULL);
	idx = 0;
	while (str[idx] != '\0' && !ft_is_delimiter(str[idx], delim))
	{
		word[idx] = str[idx];
		idx++;
	}
	word[idx] = '\0';
	return (word);
}

char	**ft_split(char *str, char delim)
{
	int		idx;
	char	**split;

	idx = 0;
	split = (char **)malloc(sizeof(char *) * ft_words_len(str, delim) + 1);
	if (!split)
		return (NULL);
	while (*str)
	{
		while (*str && ft_is_delimiter(*str, delim))
			str++;
		if (*str && !ft_is_delimiter(*str, delim))
		{
			split[idx] = ft_get_word(str, delim);
			idx++;
		}
		while (*str && !ft_is_delimiter(*str, delim))
			str++;
	}
	split[idx] = NULL;
	return (split);
}
