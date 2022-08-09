/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:34 by donghyle          #+#    #+#             */
/*   Updated: 2022/08/09 18:08:39 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buff_stored, char *buff_read)
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
		free(buff_stored);
		if (!temp)
			return (NULL);
		buff_stored = temp;
	}
	return (buff_stored);
}

static char	*extract_line(char *buff)
{
	char	*new;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	new = (char *)malloc(i + 2);
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

static char	*update_buff(char *buff)
{
	size_t	len;
	size_t	i;
	char	*new_buff;

	len = 0;
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	new_buff = (char *)malloc((ft_strchr(buff, '\0') - buff) - i + 1);
	if (!new_buff)
	{
		free(buff);
		return (NULL);
	}
	i++;
	while (buff[i] != '\0')
		new_buff[len++] = buff[i++];
	new_buff[len] = '\0';
	free(buff);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	char		*new_line;
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
	buff_read = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff_read)
		return (NULL);
	buff_stored = read_line(fd, buff_stored, buff_read);
	free(buff_read);
	if (!buff_stored)
		return (NULL);
	new_line = extract_line(buff_stored);
	buff_stored = update_buff(buff_stored);
	return (new_line);
}
