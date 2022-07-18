#include "get_next_line_bonus.h"
#include <stdio.h>

t_list	*create_list()
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->cap = LIST_SIZE;
	new_list->len = 0;
	new_list->data = (t_fdbuffer *)malloc(sizeof(t_fdbuffer) * LIST_SIZE);
	if (!(new_list->data))
	{
		free(new_list);
		return (NULL);
	}
	return (new_list);
}

int	append_list(t_list *list, t_fdbuffer new_data)
{
	t_fdbuffer	*temp;
	int			i;

	if (list->cap == list->len)
	{
		list->cap += LIST_SIZE;
		temp = (t_fdbuffer *)malloc(sizeof(t_fdbuffer) * list->cap);
		if (!temp)
		{
			list->cap -= LIST_SIZE;
			return (CODE_ERROR_MALLOC);
		}
		i = -1;
		while (++i < list->len)
			temp[i] = list->data[i];
		free(list->data);
		list->data = temp;
	}
	list->data[list->len] = new_data;
	list->len++;
	return (CODE_OK);
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
	len_prev = 0;
	while ((*buf_prev)[len_prev])
		len_prev++;
	line = ft_substr(*buf_prev, 0, len_line);
	if (!line)
		return (NULL);
	temp = ft_substr(*buf_prev, len_line, len_prev - len_line);
	free(*buf_prev);
	*buf_prev = temp;
	// printf(">>> ft_split_at: buf_prev: %p: \"%s\"\n", *buf_prev, *buf_prev);
	return (line);
}
