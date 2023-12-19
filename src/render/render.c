/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:25:10 by seunan            #+#    #+#             */
/*   Updated: 2023/12/19 11:07:48 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "render.h"
#include "ray.h"

void	render(t_vars *vars)
{
	int			i;
	int			j;
	t_vec3		pixel_center;
	t_color3	color;

	i = -1;
	j = -1;
	vars->ray.orig = vars->camera.view_point;
	while (++j < HEIGHT)
	{
		i = 0;
		while (++i < WIDTH)
		{
			pixel_center = v_plus(vars->camera.pixel_00_loc, \
			v_plus(vt_mul(vars->camera.pixel_delta_u, i), \
			vt_mul(vars->camera.pixel_delta_v, j)));
			vars->ray.dir = v_minus(pixel_center, vars->camera.view_point);
			color = ray_color(vars);
			color = get_color_real_to_int(color);
			my_mlx_pixel_put(&vars->mlx_data, i, j, create_trgb(0, &color));
		}
	}
}
