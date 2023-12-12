/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 11:40:32 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structures.h"
#include "matrix.h"
#include "vector.h"
#include <stdlib.h>
#include <math.h>

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_vars		vars;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvaild number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	init_mlx(&mlx_data);
	vars.camera.direct_v.x = 0.0;
	vars.camera.direct_v.y = 0.0;
	vars.camera.direct_v.z = 1.0;
	vars.camera.view_point.x = -50.0;
	vars.camera.view_point.y = 0;
	vars.camera.view_point.z = 20;
	vars.camera.fov = 70.0;
	world2view(&vars);
	execute_mlx(&mlx_data);
	return (0);
}
