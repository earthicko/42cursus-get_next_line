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
# define LIST_SIZE 10

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
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
t_list	*create_list(void);
int		append_list(t_list **list, t_fdbuffer new_data);
int		init_fdbuffer(t_list **buff_list, int i, int fd);

#endif
