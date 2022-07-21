/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:15:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/21 12:15:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*create_list(void)
{
	t_list	*new_list;
	size_t	size_struct;

	size_struct = sizeof(t_list) + sizeof(t_fdbuffer) * LIST_SIZE;
	new_list = (t_list *)malloc(size_struct);
	if (!new_list)
		return (NULL);
	new_list->cap = LIST_SIZE;
	new_list->len = 0;
	return (new_list);
}

int	append_list(t_list **list, t_fdbuffer new_data)
{
	t_list	*temp;
	size_t	size_struct;
	int		i;

	if ((*list)->cap == (*list)->len)
	{
		(*list)->cap += LIST_SIZE;
		size_struct = sizeof(t_list) + sizeof(t_fdbuffer) * (*list)->cap;
		temp = (t_list *)malloc(size_struct);
		if (!temp)
		{
			(*list)->cap -= LIST_SIZE;
			return (CODE_ERROR_MALLOC);
		}
		temp->len = (*list)->len;
		temp->cap = (*list)->cap;
		i = -1;
		while (++i < (*list)->len)
			temp->arr[i] = (*list)->arr[i];
		free(*list);
		*list = temp;
	}
	(*list)->arr[(*list)->len] = new_data;
	(*list)->len++;
	return (CODE_OK);
}

char	*ft_strchr(const char *s, int c)
{
	char	*cursor;

	cursor = (char *) s;
	c = (int)(char) c;
	while (*cursor != '\0')
	{
		if (*cursor == c)
			return (cursor);
		cursor++;
	}
	if (c == '\0')
		return (cursor);
	else
		return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	i;
	char	*substr;

	len_s = ft_strchr(s, '\0') - s;
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

char	*ft_split_at(char **buf_prev)
{
	char	*line;
	char	*temp;
	char	*ptr_nl;
	size_t	len_line;
	size_t	len_prev;

	ptr_nl = ft_strchr(*buf_prev, '\n');
	if (!ptr_nl)
		return (NULL);
	len_line = ptr_nl - *buf_prev + 1;
	len_prev = ft_strchr(*buf_prev, '\0') - *buf_prev;
	line = ft_substr(*buf_prev, 0, len_line);
	temp = ft_substr(*buf_prev, len_line, len_prev - len_line);
	free(*buf_prev);
	*buf_prev = temp;
	return (line);
}
