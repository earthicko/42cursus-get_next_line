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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
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
