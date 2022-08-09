/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/08/09 18:08:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_line(t_list *buff_stored, int fd, char *buff_read)
{
	int		file_len;
	char	*temp;

	file_len = 1;
	while (file_len != 0 && ft_strchr(buff_stored->buff, '\n') == 0)
	{
		file_len = read(fd, buff_read, BUFFER_SIZE);
		if (file_len == -1)
			return (CODE_ERROR_IO);
		buff_read[file_len] = '\0';
		temp = ft_strjoin(buff_stored->buff, buff_read);
		if (!temp)
			return (CODE_ERROR_MALLOC);
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
	if (buff_stored->buff[i] == '\0' || !new_buff)
	{
		del_list(buff_list, buff_stored);
		if (new_buff)
			free(new_buff);
		return ;
	}
	i++;
	while (buff_stored->buff[i] != '\0')
		new_buff[len++] = buff_stored->buff[i++];
	new_buff[len] = '\0';
	free(buff_stored->buff);
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
		cursor = init_list(buff_list, fd);
		if (!cursor)
			return (NULL);
	}
	if (cursor->buff == NULL)
	{
		cursor->buff = (char *)malloc(1);
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
	if (!buff_read)
		return (NULL);
	res = read_line(buff_stored, fd, buff_read);
	free(buff_read);
	if (res < 0)
		return (del_list(&buff_list, buff_stored));
	new_line = extract_line(buff_stored);
	update_buff(&buff_list, buff_stored);
	return (new_line);
}
