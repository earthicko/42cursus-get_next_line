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
#include <stdio.h>
typedef struct s_list
{
	int				fd;
	char			*buff;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

#endif
