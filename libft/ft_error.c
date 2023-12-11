#include <stdlib.h>
#include "libft.h"

void	ft_error(char *msg)
{
	ft_putendl_fd("\033[0;31mError", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("\033[0m", 2);
	exit(EXIT_FAILURE);
}
