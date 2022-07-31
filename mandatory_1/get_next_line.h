#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_new_buff(char *buff);
char	*ft_read_line(int fd, char *buff_stored, char *buff_read);
char	*ft_define_line(char *buff);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

#endif
