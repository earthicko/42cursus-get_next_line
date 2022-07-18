#include "get_next_line_bonus.h"
#include <unistd.h>

static char	*handle_eof(char **buf_prev)
{
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

static int	init_get_next_line(int fd, char **buf_prev)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (CODE_ERROR_SCOPE);
	if (!(*buf_prev))
	{
		*buf_prev = (char *)malloc(sizeof(char));
		if (!(*buf_prev))
			return (CODE_ERROR_MALLOC);
		(*buf_prev)[0] = '\0';
	}
	return (CODE_OK);
}

char	*get_next_line(int fd)
{
	static char	*buf_prev;
	char		buf_curr[BUFFER_SIZE + 1];
	char		*ptr_nl;
	int			stat;

	if (init_get_next_line(fd, &buf_prev) < 0)
		return (NULL);
	while (1)
	{
		ptr_nl = ft_strchr(buf_prev, '\n');
		if (ptr_nl)
			return (ft_split_at(&buf_prev, ptr_nl));
		stat = read(fd, buf_curr, BUFFER_SIZE);
		if (stat < 0)
		{
			free(buf_prev);
			buf_prev = NULL;
			return (NULL);
		}
		if (stat == 0)
			return (handle_eof(&buf_prev));
		buf_curr[stat] = '\0';
		if (handle_read_buf(&buf_prev, buf_curr, stat) < 0)
			return (NULL);
	}
}
