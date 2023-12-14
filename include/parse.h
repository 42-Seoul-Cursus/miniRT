#ifndef PARSE_H
# define PARSE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1048575
# endif

# include <stdlib.h>

// get_next_line
char	*get_next_line(int fd);
char	*repeat_read(char **backup, int fd, char *buf, int size);
char	*ret_line(char **backup);
char	*update_line(char **backup, char *line, char *cut);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);

#endif
