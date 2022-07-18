#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdio.h>

static char	*handle_eof(char **buf_prev)
{
	// printf(">>> handle eof\n");
	char	*line;

	if (*buf_prev == NULL)
		return (NULL);
	if ((*buf_prev)[0] == '\0')
	{
		free(*buf_prev);
		*buf_prev = NULL;
		return (NULL);
	}
	else
	{
		line = *buf_prev;
		*buf_prev = NULL;
		return (line);
	}
}

static int	handle_read_buf(char **buf_prev, char *buf_curr, int stat)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while ((*buf_prev)[++i]);
	while (buf_curr[++j]);
	temp = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!temp)
	{
		free(*buf_prev);
		*buf_prev = NULL;
		return (CODE_ERROR_MALLOC);
	}
	i = -1;
	j = -1;
	while ((*buf_prev)[++i])
		temp[i] = (*buf_prev)[i];
	while (buf_curr[++j])
		temp[i + j] = buf_curr[j];
	temp[i + j] = '\0';
	free(*buf_prev);
	*buf_prev = temp;
	return (CODE_OK);
}

static int	init_fdbuffer(int fd, char ***ptr_buf_prev, t_list **buffers)
{
	int			i;
	t_fdbuffer	new_buf;

	i = -1;
	while (++i < (*buffers)->len)
	{
		if ((*buffers)->data[i].fd == fd)
			break;
	}
	if (i == (*buffers)->len)
	{
		new_buf.buf = (char *)malloc(sizeof(char));
		if (!new_buf.buf)
			return (CODE_ERROR_MALLOC);
		new_buf.buf[0] = '\0';
		new_buf.fd = fd;
		// printf(">>> init_fdbuffer: created buf %p fd %d\n", new_buf.buf, new_buf.fd);
		if (append_list(*buffers, new_buf) < 0)
		{
			free(new_buf.buf);
			return (CODE_ERROR_MALLOC);
		}
	}
	*ptr_buf_prev = &((*buffers)->data[i].buf);
	return (CODE_OK);
}

static int	init_get_next_line(int fd, char ***ptr_buf_prev, t_list **buffers)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (CODE_ERROR_SCOPE);
	if (!(*buffers))
	{
		// printf(">>> init_get_next_line: no t_list found, creating\n");
		*buffers = create_list();
		if (!(*buffers))
			return (CODE_ERROR_MALLOC);
	}
	if (init_fdbuffer(fd, ptr_buf_prev, buffers) < 0)
		return (CODE_ERROR_MALLOC);
	if (!(**ptr_buf_prev))
	{
		**ptr_buf_prev = (char *)malloc(sizeof(char));
		if (!(**ptr_buf_prev))
			return (CODE_ERROR_MALLOC);
		(**ptr_buf_prev)[0] = '\0';
	}
	return (CODE_OK);
}

char	*get_next_line(int fd)
{
	static t_list	*buffers;
	char			**ptr_buf_prev;
	char			buf_curr[BUFFER_SIZE + 1];
	int				stat;

	if (init_get_next_line(fd, &ptr_buf_prev, &buffers) < 0)
		return (NULL);
	// printf(">>> get_next_line: fd %d buf %p: \"%s\"\n", fd, *ptr_buf_prev, *ptr_buf_prev);
	while (1)
	{
		if (ft_strchr(*ptr_buf_prev, '\n'))
			return (ft_split_at(ptr_buf_prev));
		stat = read(fd, buf_curr, BUFFER_SIZE);
		// printf(">>> get_next_line: stat %d, buf \"%s\"\n", stat, buf_curr);
		if (stat < 0)
		{
			free(*ptr_buf_prev);
			*ptr_buf_prev = NULL;
			return (NULL);
		}
		if (stat == 0)
			return (handle_eof(ptr_buf_prev));
		buf_curr[stat] = '\0';
		if (handle_read_buf(ptr_buf_prev, buf_curr, stat) < 0)
			return (NULL);
	}
}
