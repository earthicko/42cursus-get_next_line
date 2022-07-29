/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:15:35 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/21 12:15:37 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

static char	*handle_eof(t_linereader *l)
{
	char	*line;

	if (*(l->ptr_buf_prev) == NULL)
		return (NULL);
	if ((*(l->ptr_buf_prev))[0] == '\0')
	{
		free(*(l->ptr_buf_prev));
		*(l->ptr_buf_prev) = NULL;
		return (NULL);
	}
	else
	{
		line = *(l->ptr_buf_prev);
		*(l->ptr_buf_prev) = NULL;
		return (line);
	}
}

static int	handle_read_buf(t_linereader *l)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = ft_strchr(*(l->ptr_buf_prev), '\0') - *(l->ptr_buf_prev);
	j = ft_strchr(l->buf_curr, '\0') - l->buf_curr;
	temp = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!temp)
	{
		free(*(l->ptr_buf_prev));
		*(l->ptr_buf_prev) = NULL;
		return (CODE_ERROR_MALLOC);
	}
	i = -1;
	j = -1;
	while ((*(l->ptr_buf_prev))[++i])
		temp[i] = (*(l->ptr_buf_prev))[i];
	while ((l->buf_curr)[++j])
		temp[i + j] = (l->buf_curr)[j];
	temp[i + j] = '\0';
	free(*(l->ptr_buf_prev));
	*(l->ptr_buf_prev) = temp;
	return (CODE_OK);
}

static int	init_fdbuffer(int fd, t_linereader *l)
{
	int			i;
	t_fdbuffer	new_buf;

	i = -1;
	while (++i < l->buffers->len)
	{
		if (l->buffers->arr[i].fd == fd)
			break ;
	}
	if (i == l->buffers->len)
	{
		new_buf.buf = (char *)malloc(sizeof(char));
		if (!new_buf.buf)
			return (CODE_ERROR_MALLOC);
		new_buf.buf[0] = '\0';
		new_buf.fd = fd;
		if (append_list(&(l->buffers), new_buf) < 0)
		{
			free(new_buf.buf);
			return (CODE_ERROR_MALLOC);
		}
	}
	l->ptr_buf_prev = &(l->buffers->arr[i].buf);
	return (CODE_OK);
}

static int	init_get_next_line(int fd, t_linereader *l)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (CODE_ERROR_SCOPE);
	if (!(l->buffers))
	{
		l->buffers = create_list();
		if (!(l->buffers))
			return (CODE_ERROR_MALLOC);
	}
	if (!(l->buf_curr))
	{
		l->buf_curr = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(l->buf_curr))
			return (CODE_ERROR_MALLOC);
	}
	if (init_fdbuffer(fd, l) < 0)
		return (CODE_ERROR_MALLOC);
	if (!(*(l->ptr_buf_prev)))
	{
		*(l->ptr_buf_prev) = (char *)malloc(sizeof(char));
		if (!(*(l->ptr_buf_prev)))
			return (CODE_ERROR_MALLOC);
		(*(l->ptr_buf_prev))[0] = '\0';
	}
	return (CODE_OK);
}

char	*get_next_line(int fd)
{
	static t_linereader	l;

	if (init_get_next_line(fd, &l) < 0)
		return (NULL);
	while (1)
	{
		if (ft_strchr(*(l.ptr_buf_prev), '\n'))
			return (ft_split_at(l.ptr_buf_prev));
		l.stat = read(fd, l.buf_curr, BUFFER_SIZE);
		if (l.stat < 0)
		{
			free(*(l.ptr_buf_prev));
			*(l.ptr_buf_prev) = NULL;
			free(l.buf_curr);
			return (NULL);
		}
		if (l.stat == 0)
			return (handle_eof(&l));
		l.buf_curr[l.stat] = '\0';
		if (handle_read_buf(&l) < 0)
			return (NULL);
	}
}
