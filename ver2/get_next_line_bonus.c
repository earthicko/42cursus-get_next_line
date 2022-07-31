#include "get_next_line_bonus.h"

static t_list	*del_list(t_list **buff_list, t_list *target)
{
	t_list	*cursor;
	t_list	*prev;

	if (*buff_list == target)
	{
		// printf("free %p *buff_list from del_list\n", *buff_list);
		*buff_list = target->next;
		free(*buff_list);
		*buff_list = NULL;
		return (NULL);
	}
	cursor = (*buff_list)->next;
	prev = *buff_list;
	while (cursor != NULL)
	{
		if (cursor == target)
		{
			prev->next = cursor->next;
			free(cursor->buff);
			// printf("free %p cursor->buff from del_list\n", cursor->buff);
			free(cursor);
			// printf("free %p cursor from del_list\n", cursor);
			return (NULL);
		}
		cursor = cursor->next;
		prev = prev->next;
	}
	return (NULL);
}

static int	read_line(t_list **buff_list, t_list *buff_stored, int fd, char *buff_read)
{
	int		file_len;
	char	*temp;

	file_len = 1;
	while (file_len != 0 && ft_strchr(buff_stored->buff, '\n') == 0)
	{
		file_len = read(fd, buff_read, BUFFER_SIZE);
		if (file_len == -1)
		{
			del_list(buff_list, buff_stored);
			return (CODE_ERROR_IO);
		}
		buff_read[file_len] = '\0';
		temp = ft_strjoin(buff_stored->buff, buff_read);
		if (!temp)
		{
			del_list(buff_list, buff_stored);
			return (CODE_ERROR_MALLOC);
		}
		buff_stored->buff = temp;
	}
	return (CODE_OK);
}

static char	*extract_line(t_list *buff_stored)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!buff_stored->buff[i])
		return (NULL);
	while (buff_stored->buff[i] != '\n' && buff_stored->buff[i] != '\0')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 2));
	// printf("malloc %p new_line from extract_line\n", new_line);
	if (!new_line)
		return (NULL);
	i = 0;
	while (1)
	{
		new_line[i] = buff_stored->buff[i];
		if (buff_stored->buff[i] == '\0' || buff_stored->buff[i] == '\n')
			break ;
		i++;
	}
	new_line[++i] = '\0';
	return (new_line);
}

static void	update_buff(t_list **buff_list, t_list *buff_stored)
{
	size_t	len;
	size_t	len_new;
	size_t	i;
	char	*new_buff;

	len = 0;
	i = 0;
	while (buff_stored->buff[i] != '\n' && buff_stored->buff[i] != '\0')
		i++;
	len_new = (ft_strchr(buff_stored->buff, '\0') - buff_stored->buff) - i + 1;
	new_buff = (char *)malloc(len_new);
	// printf("malloc %p new_buff from update_buff\n", new_buff);
	if (buff_stored->buff[i] == '\0' || !new_buff)
	{
		del_list(buff_list, buff_stored);
		if (new_buff)
		{
			free(new_buff);
			// printf("free %p new_buff from update_buff\n", new_buff);
		}
		return ;
	}
	i++;
	while (buff_stored->buff[i] != '\0')
		new_buff[len++] = buff_stored->buff[i++];
	new_buff[len] = '\0';
	free(buff_stored->buff);
	// printf("free %p buff_stored->buff from update_buff\n", buff_stored->buff);
	buff_stored->buff = new_buff;
}

static t_list	*assign_buff(t_list **buff_list, int fd)
{
	t_list	*cursor;

	cursor = *buff_list;
	while (cursor != NULL)
	{
		if (cursor->fd == fd)
			break ;
		cursor = cursor->next;
	}
	if (cursor == NULL)
	{
		cursor = (t_list *)malloc(sizeof(t_list));
		// printf("malloc %p cursor from assign_buff\n", cursor);
		if (!cursor)
			return (NULL);
		cursor->fd = fd;
		cursor->buff = NULL;
		cursor->next = *buff_list;
		*buff_list = cursor;
	}
	if (cursor->buff == NULL)
	{
		cursor->buff = (char *)malloc(1);
		// printf("malloc %p cursor->buff from assign_buff\n", cursor->buff);
		if (!cursor->buff)
			return (del_list(buff_list, cursor));
		cursor->buff[0] = '\0';
	}
	return (cursor);
}

char	*get_next_line(int fd)
{
	char			*new_line;
	char			*buff_read;
	static t_list	*buff_list;
	t_list			*buff_stored;
	int				res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff_stored = assign_buff(&buff_list, fd);
	if (!buff_stored)
		return (NULL);
	buff_read = (char *)malloc((sizeof(char) * BUFFER_SIZE + 1));
	// printf("malloc %p buff_read from get_next_line\n", buff_read);
	if (!buff_read)
		return (NULL);
	res = read_line(&buff_list, buff_stored, fd, buff_read);
	free(buff_read);
	// printf("free %p buff_read from get_next_line\n", buff_read);
	if (res < 0)
		return (NULL);
	new_line = extract_line(buff_stored);
	update_buff(&buff_list, buff_stored);
	return (new_line);
}
