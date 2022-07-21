/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:15:54 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/21 12:15:55 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# define CODE_ERROR_MALLOC -2
# define CODE_ERROR_SCOPE -1
# define CODE_OK 0
# define LIST_SIZE 10
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fdbuffer
{
	char	*buf;
	int		fd;
}	t_fdbuffer;
typedef struct s_list
{
	int			len;
	int			cap;
	t_fdbuffer	arr[0];
}	t_list;
char	*get_next_line(int fd);
t_list	*create_list(void);
int		append_list(t_list **list, t_fdbuffer new_data);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_split_at(char **buf_prev);
#endif
