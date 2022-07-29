/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:15:38 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/21 12:15:40 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	char	*cursor;

	cursor = (char *)str;
	while (*cursor)
	{
		if (*cursor == c)
			return (cursor);
		cursor++;
	}
	if (c == '\0')
		return (cursor);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*substr;

	len_s = ft_strlen(s);
	if ((size_t) start >= len_s)
		len = 0;
	else if (len_s - (size_t) start < len)
		len = len_s - (size_t) start;
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = (s + start)[i];
		i++;
	}
	substr[len] = '\0';
	return (substr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len_1;
	size_t	len_2;
	char	*joined;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < len_1)
	{
		joined[i] = s1[i];
		i++;
	}
	while (i < len_1 + len_2)
	{
		joined[i] = s2[i - len_1];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*ft_split_at(char **buf_prev, char *ptr_nl)
{
	char	*line;
	char	*temp;
	size_t	len_line;
	size_t	len_prev;

	if (!ptr_nl)
		return (NULL);
	len_line = ptr_nl - *buf_prev + 1;
	len_prev = ft_strlen(*buf_prev);
	line = ft_substr(*buf_prev, 0, len_line);
	if (!line)
		return (NULL);
	temp = ft_substr(*buf_prev, len_line, len_prev - len_line);
	free(*buf_prev);
	*buf_prev = temp;
	return (line);
}
