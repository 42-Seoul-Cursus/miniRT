/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 15:10:35 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structures.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>

int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}

void	init_vars(t_vars *vars, char *path)
{
	vars->fd = protected_open(path);
}

int	main(int argc, char *argv[])
{
	t_vars		vars;
	t_mlx_data	mlx_data;

	is_valid_arg(argc, argv);
	init_vars(&vars, argv[1]);
	init_mlx(&mlx_data);
	execute_mlx(&mlx_data);
	return (0);
}
