#include <stdlib.h>
#include "minirt.h"
#include "libft.h"

void	exit_with_msg(char *msg)
{
	ft_putstr_fd("\033[0;31mError\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\033[0m", 4);
	exit(EXIT_FAILURE);
}
