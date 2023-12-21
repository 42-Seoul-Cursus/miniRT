/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:25:10 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 20:31:01 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "render.h"
#include "ray.h"

void	here(void)
{
	return ;
}
/* ray를 카메라에서 쏴서 픽셀의 값을 찍음 */
void	render(t_vars *vars)
{
	int			i;
	int			j;
	t_vec3		pixel_center;
	t_color3	color;

	j = -1;
	vars->ray.orig = vars->camera.view_point;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			pixel_center = v_plus(vars->camera.pixel_00_loc, \
			v_plus(vt_mul(vars->camera.pixel_delta_u, i), \
			vt_mul(vars->camera.pixel_delta_v, j)));
			vars->ray.dir = v_minus(pixel_center, vars->camera.view_point);
			if (j == HEIGHT - 1)
				here();
			color = ray_color(vars);
			color = get_color_real_to_int(color);
			my_mlx_pixel_put(&vars->mlx_data, i, j, create_trgb(0, &color));
		}
	}
}
