/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 16:26:33 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structures.h"
#include <stdlib.h>

void	world2view(t_camera *camera, t_list *object)
{

}

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_camera	camera;
	t_list		objects;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvaild number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	init_mlx(&mlx_data);
	camera.direct_v.x = 0.0;
	camera.direct_v.y = 0.0;
	camera.direct_v.z = 1.0;
	camera.view_point.x = -50.0;
	camera.view_point.y = 0;
	camera.view_point.z = 20;
	camera.fov = 70.0;
	world2view(&camera);
	execute_mlx(&mlx_data);
	return (0);
}
