/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 22:23:24 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>

int	hit_obj(t_list *object, t_ray *ray, t_hit_record *rec)
{
	int		is_hit;

	is_hit = 0;
	if (object->type == SPHERE)
		is_hit = hit_sphere((t_sphere *)object->content, ray, rec);
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

t_color3	ray_color(t_ray *ray, t_list *objects)
{
	t_hit_record	rec;
	t_vec3			unit_direction;
	double			a;

	rec.tmin = 1e-6;
	rec.tmax = INFINITY;
	if (hit(objects, ray, &rec))
		return (vt_mul(\
		v_plus(rec.normal, \
		color3(255.999 * (rec.normal.x + 1), 255.999 * (rec.normal.y + 1), \
		255.999 * (rec.normal.z + 1))), 0.4));
	unit_direction = v_unit(ray->dir);
	a = 0.5 * (unit_direction.x + 1.0);
	return (v_plus(\
	vt_mul(color3(255.0, 255.0, 255.0), (1.0 - a)), \
	vt_mul(color3(170.0, 200.0, 255.0), a)));
}

void	render(t_vars *vars, t_mlx_data *mlx)
{
	int			i;
	int			j;
	t_vec3		pixel_center;
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
			pixel_center = v_plus(vars->camera.poxel_00_loc, \
			v_plus(vt_mul(vars->camera.pixel_delta_u, i), \
			vt_mul(vars->camera.pixel_delta_v, j)));
			ray.dir = v_minus(pixel_center, vars->camera.view_point);
			color = ray_color(&ray, vars->objects);
			my_mlx_pixel_put(mlx, i, j, create_trgb(0, &color));
		}
	}
}
