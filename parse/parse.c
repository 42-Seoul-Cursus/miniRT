#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include "../minirt.h"

static int	protected_open(char *path);

void	init_vars(t_vars *vars)
{
	vars->ambient.b_start = 0;
	vars->camera.b_start = 0;
	vars->light.b_start = 0;
}

void	check_type(t_vars *vars, char *buf)
{
	while (*buf == ' ')
		buf++;
	// {
	// 	/* code */
	// }

	// if ()
}

void	parse_rt(t_vars *vars, char *path)
{
	char	*buf;
	int		fd;

	fd = protected_open(path);
	while (1)
	{
		buf = get_next_line(fd);
		if (buf == NULL)
			break ;
		check_type(vars, buf);
		free(buf);
	}
}

static int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}


