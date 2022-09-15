/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:41 by donghyle          #+#    #+#             */
/*   Updated: 2022/08/09 18:08:42 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	read_line(t_list *buff_stored, int fd, char *buff_read)
{
	int		file_len;
	char	*temp;

	file_len = 1;
	// 아무것도 읽은 것이 없거나 읽은 내용 중 \n 포함 시 중지
	while (file_len != 0 && ft_strchr(buff_stored->buff, '\n') == 0)
	{
		file_len = read(fd, buff_read, BUFFER_SIZE);
		if (file_len == -1)
			return (CODE_ERROR_IO);
		buff_read[file_len] = '\0';
		// 버퍼에 읽은 내용 덧붙임
		temp = ft_strjoin(buff_stored->buff, buff_read);
		if (!temp)
			return (CODE_ERROR_MALLOC);
		buff_stored->buff = temp;
	}
	return (CODE_OK);
}

static char	*extract_line(t_list *buff_stored)
{
	char	*new_line;
	int		i;

	i = 0;
	// 문자열 길이가 0일 시 (파일의 모든 내용을 이미 반환함) NULL 반환
	if (!buff_stored->buff[i])
		return (NULL);
	while (buff_stored->buff[i] != '\n' && buff_stored->buff[i] != '\0')
		i++;
	// \n으로 끝날 시 i + 2바이트, \0으로 끝날 시 i + 1바이트 필요하므로 더 큰 값을 선택
	new_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!new_line)
		return (NULL);
	i = 0;
	while (1)
	{
		new_line[i] = buff_stored->buff[i];
		if (buff_stored->buff[i] == '\0' || buff_stored->buff[i] == '\n')
			break ;
		i++;
	}
	new_line[++i] = '\0';
	return (new_line);
}

static void	update_buff(t_list **buff_list, t_list *buff_stored)
{
	size_t	len;
	size_t	len_new;
	size_t	i;
	char	*new_buff;

	len = 0;
	i = 0;
	while (buff_stored->buff[i] != '\n' && buff_stored->buff[i] != '\0')
		i++;
	len_new = (ft_strchr(buff_stored->buff, '\0') - buff_stored->buff) - i + 1;
	new_buff = (char *)malloc(len_new);
	// 마지막이 \0이다 = extract_line에서 이미 마지막 줄까지 추출했다 = 이 파일은 끝났다
	if (buff_stored->buff[i] == '\0' || !new_buff)
	{
		del_list(buff_list, buff_stored);
		if (new_buff)
			free(new_buff);
		return ;
	}
	i++;
	while (buff_stored->buff[i] != '\0')
		new_buff[len++] = buff_stored->buff[i++];
	new_buff[len] = '\0';
	free(buff_stored->buff);
	buff_stored->buff = new_buff;
}

static t_list	*assign_buff(t_list **buff_list, int fd)
{
	t_list	*cursor;

	// 커서를 리스트의 처음에 맞추고
	cursor = *buff_list;
	// 리스트 끝에 도달하거나 리스트가 초기화 되지 않았을 시 중지
	while (cursor != NULL)
	{
		// 일치하는 fd 발견 시 중지
		if (cursor->fd == fd)
			break ;
		cursor = cursor->next;
	}
	// 리스트가 초기화되지 않았거나 일치하는 fd가 없다면
	if (cursor == NULL)
	{
		// 노드를 추가
		cursor = init_list(buff_list, fd);
		if (!cursor)
			return (NULL);
	}
	// 새 노드를 방금 추가한 상황이라면
	if (cursor->buff == NULL)
	{
		// 길이 0의 문자열 초기화
		cursor->buff = (char *)malloc(1);
		if (!cursor->buff)
			return (del_list(buff_list, cursor));
		cursor->buff[0] = '\0';
	}
	return (cursor);
}

char	*get_next_line(int fd)
{
	char			*new_line;		// 반환될 문자열 포인터
	char			*buff_read;		// read() 함수를 수행할 대상
	static t_list	*buff_list;		// 이전에 read() 되었지만 아직 반환되지 않은 문자 리스트
	t_list			*buff_stored;	// 해당 fd에 대한 버퍼
	int				res;			// 예하 함수의 실행 결과 코드

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	// 해당 fd를 위한 버퍼를 인출해옴
	buff_stored = assign_buff(&buff_list, fd);
	if (!buff_stored)
		return (NULL);
	buff_read = (char *)malloc((sizeof(char) * BUFFER_SIZE + 1));
	if (!buff_read)
		return (NULL);
	// \n 혹은 EOF를 읽을 때까지 read()
	res = read_line(buff_stored, fd, buff_read);
	free(buff_read);
	// 에러 반환 시 버퍼를 삭제함
	if (res < 0)
		return (del_list(&buff_list, buff_stored));
	// 새 줄을 new_line에 저장
	new_line = extract_line(buff_stored);
	// 버퍼에서 새 줄을 삭제
	update_buff(&buff_list, buff_stored);
	return (new_line);
}
