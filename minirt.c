/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/11 16:26:33 by sunko            ###   ########.fr       */
=======
/*   Updated: 2023/12/11 16:13:30 by seunan           ###   ########.fr       */
>>>>>>> a42cc170d1dfede14e28fcc5c7ddfbe3a87f5c38
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "structures.h"
#include "libft.h"

void	world2view(t_camera *camera, t_list *object)
{

}

int	main(int argc, char *argv[])
{
	t_vars		vars;
	t_mlx_data	mlx_data;
	t_camera	camera;
	t_list		objects;

	is_valid_arg(argc, argv);
	init_vars(&vars);
	parse_rt(&vars, argv[1]);
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
