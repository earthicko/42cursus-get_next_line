#include "get_next_line.h"

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

char	*ft_new_buff(char *buff)
{
	size_t	len;
	size_t	i;
	char	*tmp;

	len = 0;
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	tmp = (char *)malloc((ft_strchr(buff, '\0') - buff) - i + 1);
	if (!tmp)
	{
		free(buff);
		return (NULL);
	}
	i++;
	while (buff[i] != '\0')
		tmp[len++] = buff[i++];
	tmp[len] = '\0';
	free(buff);
	return (tmp);
}
