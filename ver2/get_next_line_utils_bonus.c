/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:47 by donghyle          #+#    #+#             */
/*   Updated: 2022/08/09 18:08:48 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_list	*init_list(t_list **head, int init_fd)
{
	t_list	*init;

	init = (t_list *)malloc(sizeof(t_list));
	if (!init)
		return (NULL);
	init->fd = init_fd;
	init->buff = NULL;
	init->next = *head;
	*head = init;
	return (init);
}

void	*del_list(t_list **buff_list, t_list *target)
{
	t_list	*cursor;
	t_list	*prev;

	if (*buff_list == target)
	{
		*buff_list = target->next;
		free(target->buff);
		free(target);
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
			free(cursor);
			return (NULL);
		}
		cursor = cursor->next;
		prev = prev->next;
	}
	return (NULL);
}
