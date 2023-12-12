/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 17:29:33 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"
#include "vector.h"
#include <stdio.h>

int	create_trgb(int t, t_color3 *color)
{
	return (t << 24 | (int)color->x << 16 | (int)color->y << 8 | (int)color->z);
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_color3	ray_color(t_ray *ray)
{
	t_vec3	unit_direction;
	double	a;

	unit_direction = v_unit(ray->dir);
	a = 0.5 * (unit_direction.x + 1.0);
	return (v_plus(vt_mul(color3(255.0, 255.0, 255.0), (1.0 - a)), vt_mul(color3(170.0, 200.0, 255.0), a)));
}

void	render(t_vars *vars, t_mlx_data *mlx)
{
	int			i;
	int			j;
	t_vec3	pixel_center;
	t_ray		ray;
	t_color3	color;

	i = -1;
	j = -1;
	ray.orig = vars->camera.view_point;
	while (++j < HEIGHT)
	{
		i = 0;
		while (++i < WIDTH)
		{
			pixel_center = v_plus(vars->camera.poxel_00_loc, v_plus(vt_mul(vars->camera.pixel_delta_u, i), vt_mul(vars->camera.pixel_delta_v, j)));
			ray.dir = v_minus(pixel_center, vars->camera.view_point);
			color = ray_color(&ray);
			printf("%d %d %d\n",i, j, create_trgb(0, &color));
			my_mlx_pixel_put(mlx, i, j, create_trgb(0, &color));
		}
	}
}

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_vars		vars;

	is_valid_arg(argc, argv);
	init_vars(&vars);
	parse_rt(&vars, argv[1]);
	is_valid_rt(&vars);
	init_mlx(&mlx_data);
	world2view(&vars);
	render(&vars, &mlx_data);
	execute_mlx(&mlx_data);
	return (0);
}
