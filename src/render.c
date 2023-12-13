/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 12:36:27 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "ray.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3	get_sphere_normal_v(t_sphere *sphere, t_hit_record *rec);

int	create_trgb(int t, t_color3 *color)
{
	return (t << 24 | (int)color->x << 16 | (int)color->y << 8 | (int)color->z);
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	update_nearest_hit_point(double a, double b, double c, t_hit_record *rec)
{
	double	root;
	double	sqrtd;
	double	discriminant;

	discriminant = b * b - a * c;
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	rec->t = root;
	return (1);
}

int	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;

	oc = v_minus(ray->orig, sphere->center);
	a = v_length2(ray->dir);
	b = v_dot(oc, ray->dir);
	c = v_length2(oc) - sphere->radius * sphere->radius;
	if (b * b - a * c < 0)
		return (0.0);
	if (update_nearest_hit_point(a, b, c, rec) == 0)
		return (0.0);
	rec->p = ray_at(ray, rec->t);
	rec->normal = get_sphere_normal_v(sphere, rec);
	if (v_dot(ray->dir, rec->normal) < 0)
		rec->front_face = 1;
	else
	{
		rec->front_face = 0;
		rec->normal = vt_mul(rec->normal, -1.0);
	}
	rec->front_face = v_dot(ray->dir, rec->normal) < 0;
	return (1);
}

t_vec3	get_sphere_normal_v(t_sphere *sphere, t_hit_record *rec)
{
	t_vec3	normal_v;

	normal_v = v_unit(v_minus(rec->p, sphere->center));
	return (normal_v);
}

t_color3	get_sphere_color(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vec3	unit_direction;
	double	a;
	t_vec3	n;
	double	t;

	t = hit_sphere(sphere, ray, rec);
	if (t > 0.0)
	{
		n = get_sphere_normal_v(sphere, rec);
		return (vt_mul(\
		color3(255.999 * (n.x + 1), 255.999 * (n.y + 1), 255.999 * (n.z + 1)), 0.5));
	}
	unit_direction = v_unit(ray->dir);
	a = 0.5 * (unit_direction.x + 1.0);
	return (v_plus(\
	vt_mul(color3(255.0, 255.0, 255.0), (1.0 - a)), \
	vt_mul(color3(170.0, 200.0, 255.0), a)));
}

t_color3	ray_color(t_ray *ray, t_list *objects)
{
	t_list			*cur;
	t_hit_record	rec;

	cur = objects;
	rec.tmin = 0;
	rec.tmax = INFINITY;
	if (cur->type == SPHERE)
		return (get_sphere_color((t_sphere *)cur->content, ray, &rec));
	if (cur->type == PLANE)
		return (color3(0, 0, 0));
	else
		return (color3(100, 100, 100));
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
