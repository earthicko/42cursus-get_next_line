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

char	*ft_strchr(char *s, int c)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;
	size_t	len_joined;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len_joined = (ft_strchr(s1, '\0') - s1) + (ft_strchr(s2, '\0') - s2) + 1;
	joined = (char *)malloc(len_joined);
	if (joined == NULL)
		return (NULL);
	while (s1[j] != '\0')
		joined[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free (s1);
	return (joined);
}

int	init_fdbuffer(t_list **buff_list, int i, int fd)
{
	t_fdbuffer	new_fdbuffer;

	if (i == (*buff_list)->len)
	{
		new_fdbuffer.buf = NULL;
		new_fdbuffer.fd = fd;
		if (append_list(buff_list, new_fdbuffer) < 0)
			return (CODE_ERROR_MALLOC);
	}
	if (!(*buff_list)->arr[i].buf)
	{
		(*buff_list)->arr[i].buf = (char *)malloc(1);
		if (!(*buff_list)->arr[i].buf)
			return (CODE_ERROR_MALLOC);
		(*buff_list)->arr[i].buf[0] = '\0';
	}
	return (CODE_OK);
}
