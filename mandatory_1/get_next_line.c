#include "get_next_line.h"

char	*ft_read_line(int fd, char *buff_stored, char *buff_read)
{
	int		file_len;
	char	*temp;

	file_len = 1;
	while (file_len != 0 && ft_strchr(buff_stored, '\n') == 0)
	{
		file_len = read(fd, buff_read, BUFFER_SIZE);
		if (file_len == -1)
		{
			free(buff_stored);
			return (NULL);
		}
		buff_read[file_len] = '\0';
		temp = ft_strjoin(buff_stored, buff_read);
		if (!temp)
		{
			free(buff_stored);
			return (NULL);
		}
		buff_stored = temp;
	}
	return (buff_stored);
}

char	*ft_define_line(char *buff)
{
	char	*new;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	new = (char *) malloc (sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (1)
	{
		new[i] = buff[i];
		if (buff[i] == '\0' || buff[i] == '\n')
			break ;
		i++;
	}
	new[++i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char		*new;
	char		*buff_read;
	static char	*buff_stored;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buff_stored)
	{
		buff_stored = (char *)malloc(1);
		if (!buff_stored)
			return (NULL);
		buff_stored[0] = '\0';
	}
	buff_read = (char *) malloc ((sizeof(char) * BUFFER_SIZE + 1));
	if (!buff_read)
		return (NULL);
	buff_stored = ft_read_line(fd, buff_stored, buff_read);
	free(buff_read);
	if (!buff_stored)
		return (NULL);
	new = ft_define_line(buff_stored);
	buff_stored = ft_new_buff(buff_stored);
	return (new);
}
