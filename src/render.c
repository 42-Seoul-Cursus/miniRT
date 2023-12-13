/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 23:55:17 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int	hit_obj(t_list *object, t_ray *ray, t_hit_record *rec)
{
	int		is_hit;

	is_hit = 0;
	if (object->type == SPHERE)
		is_hit = hit_sphere((t_sphere *)object->content, ray, rec);
	rec->albedo = object->albedo;
	return (is_hit);
}

int	hit(t_list *objects, t_ray *ray, t_hit_record *rec)
{
	int				is_hit;
	t_hit_record	temp_rec;

	is_hit = 0;
	temp_rec = *rec;
	while (objects)
	{
		if (hit_obj(objects, ray, &temp_rec))
		{
			is_hit = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		objects = objects->next;
	}
	return (is_hit);
}

int	in_shadow(t_list *object, t_ray ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 1e-6;
	rec.tmax = light_len;
	if (hit(object, &ray, &rec))
		return (1);
	return (0);
}

t_color3	ray_color(t_vars *vars)
{
	vars->rec.tmin = 1e-6;
	vars->rec.tmax = INFINITY;
	if (hit(vars->objects, &vars->ray, &vars->rec))
		return (execute_phong(vars));
	return (color3(0.2, 0.4, 0.9));
}

void	render(t_vars *vars, t_mlx_data *mlx)
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
			pixel_center = v_plus(vars->camera.poxel_00_loc, \
			v_plus(vt_mul(vars->camera.pixel_delta_u, i), \
			vt_mul(vars->camera.pixel_delta_v, j)));
			vars->ray.dir = v_minus(pixel_center, vars->camera.view_point);
			color = ray_color(vars);
			color = get_color_real_to_int(color);
			my_mlx_pixel_put(mlx, i, j, create_trgb(0, &color));
		}
	}
}
