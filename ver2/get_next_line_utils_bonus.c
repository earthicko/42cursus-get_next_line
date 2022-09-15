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

// 개행 문자를 찾는 데 사용되고, ft_strchr(str, \0) - str로 문자열의 길이를 구할 수 있음
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

// head가 가리키는 자리에 새 노드를 만들고 리스트의 맨 앞으로 설정
t_list	*init_list(t_list **head, int init_fd)
{
	t_list	*init;

	init = (t_list *)malloc(sizeof(t_list));
	if (!init)
		return (NULL);
	init->fd = init_fd;
	init->buff = NULL;
	// init이 리스트의 맨 앞이 되어야 하므로 기존의 head를 next로 설정
	// head 자리에 NULL이 있었다면 (초기화되지 않았다면) 자연스럽게 리스트의 마지막을 표시하게 됨
	init->next = *head;
	// head가 가리키는 자리에 init을 놓음
	*head = init;
	return (init);
}

// buff_list가 리스트의 맨 앞을 가리킬 때 리스트에서 target을 찾아서 삭제
void	*del_list(t_list **buff_list, t_list *target)
{
	t_list	*cursor;
	t_list	*prev;

	// target이 맨 앞과 일치시
	if (*buff_list == target)
	{
		// 다음 노드가 맨 앞이 됨
		*buff_list = target->next;
		free(target->buff);
		free(target);
		return (NULL);
	}
	// target이 맨 앞이 아니므로 커서를 두번째 노드로 설정
	cursor = (*buff_list)->next;
	// 리스트 연결 상태를 바로잡기 위해 prev 커서를 첫 노드로 설정
	prev = *buff_list;
	// 리스트의 끝에 도달할 때까지
	while (cursor != NULL)
	{
		if (cursor == target)
		{
			// 이전 노드의 다음 노드를 커서 다음 노드로 설정
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
