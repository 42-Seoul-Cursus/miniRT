#include "libft.h"

void	is_valid_arg(int ac, char *av[])
{
	int	i;
	int	slash;

	if (ac != 2)
		ft_error("Invalid number of arguments");
	i = 0;
	slash = 0;
	while (av[1][i] != '\0')
	{
		if (av[1][i] == '/')
			slash = i + 1;
		++i;
	}
	if (i - slash < 4 || av[1][i - 1] != 't'
		|| av[1][i - 2] != 'r' || av[1][i - 3] != '.')
		ft_error("The file must end with a \'.rt\'");
}
