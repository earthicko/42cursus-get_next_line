/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:08:54 by donghyle          #+#    #+#             */
/*   Updated: 2022/08/09 18:08:55 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define CODE_ERROR_IO -3
# define CODE_ERROR_MALLOC -2
# define CODE_ERROR_SCOPE -1
# define CODE_OK 0

typedef struct s_list
{
	int				fd;		// 이 노드가 담당하는 fd
	char			*buff;	// 해당 fd에서 읽은 내용의 버퍼
	struct s_list	*next;	// 다음 노드
}					t_list;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
void	*del_list(t_list **buff_list, t_list *target);
t_list	*init_list(t_list **head, int init_fd);

#endif
