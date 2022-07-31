#include "get_next_line_bonus.h"

static int	read_line(int fd, char **buff_stored, char *buff_read)
{
	int		file_len;
	char	*temp;

	file_len = 1;
	while (file_len != 0 && ft_strchr(*buff_stored, '\n') == 0)
	{
		file_len = read(fd, buff_read, BUFFER_SIZE);
		if (file_len == -1)
		{
			free(*buff_stored);
			*buff_stored = NULL;
			return (CODE_ERROR_IO);
		}
		buff_read[file_len] = '\0';
		temp = ft_strjoin(*buff_stored, buff_read);
		if (!temp)
		{
			free(*buff_stored);
			*buff_stored = NULL;
			return (CODE_ERROR_MALLOC);
		}
		*buff_stored = temp;
	}
	return (CODE_OK);
}

static char	*extract_line(char **buff)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!(*buff)[i])
		return (NULL);
	while ((*buff)[i] != '\n' && (*buff)[i] != '\0')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (1)
	{
		new_line[i] = (*buff)[i];
		if ((*buff)[i] == '\0' || (*buff)[i] == '\n')
			break ;
		i++;
	}
	new_line[++i] = '\0';
	return (new_line);
}

static void	update_buff(char **buff_stored)
{
	size_t	len;
	size_t	len_new;
	size_t	i;
	char	*new_buff;

	len = 0;
	i = 0;
	while ((*buff_stored)[i] != '\n' && (*buff_stored)[i] != '\0')
		i++;
	len_new = (ft_strchr((*buff_stored), '\0') - (*buff_stored)) - i + 1;
	new_buff = (char *)malloc(len_new);
	if ((*buff_stored)[i] == '\0' || !new_buff)
	{
		free(*buff_stored);
		*buff_stored = NULL;
		if (new_buff)
			free(new_buff);
		return ;
	}
	i++;
	while ((*buff_stored)[i] != '\0')
		new_buff[len++] = (*buff_stored)[i++];
	new_buff[len] = '\0';
	free(*buff_stored);
	*buff_stored = new_buff;
}

static char	**assign_buff(t_list **buff_list, int fd)
{
	int			i;

	if (!(*buff_list))
	{
		*buff_list = create_list();
		if (!(*buff_list))
			return (NULL);
	}
	i = 0;
	while (i < (*buff_list)->len)
	{
		if ((*buff_list)->arr[i].fd == fd)
			break ;
		i++;
	}
	if (init_fdbuffer(buff_list, i, fd) < 0)
		return (NULL);
	return (&((*buff_list)->arr[i].buf));
}

char	*get_next_line(int fd)
{
	char			*new_line;
	char			*buff_read;
	static t_list	*buff_list;
	char			**buff_stored;
	int				res;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff_stored = assign_buff(&buff_list, fd);
	if (!buff_stored)
		return (NULL);
	buff_read = (char *)malloc((sizeof(char) * BUFFER_SIZE + 1));
	if (!buff_read)
		return (NULL);
	res = read_line(fd, buff_stored, buff_read);
	free(buff_read);
	if (res < 0)
		return (NULL);
	new_line = extract_line(buff_stored);
	update_buff(buff_stored);
	return (new_line);
}
