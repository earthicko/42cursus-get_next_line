#include "get_next_line_bonus.h"

char	*ft_strchr(const char *str, int c)
{
	char	*cursor;

	cursor = (char *)str;
	while (*cursor)
	{
		if (*cursor == c)
			return (cursor);
		cursor++;
	}
	if (c == '\0')
		return (cursor);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_split_at(char **buf_prev, char *ptr_nl)
{
	char	*line;
	char	*temp;
	size_t	len_line;
	size_t	len_prev;

	if (!ptr_nl)
		return (NULL);
	len_line = ptr_nl - *buf_prev + 1;
	len_prev = 0;
	while ((*buf_prev)[len_prev])
		len_prev++;
	line = ft_substr(*buf_prev, 0, len_line);
	if (!line)
		return (NULL);
	temp = ft_substr(*buf_prev, len_line, len_prev - len_line);
	free(*buf_prev);
	*buf_prev = temp;
	return (line);
}
