/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 21:51:16 by seunan           ###   ########.fr       */
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

t_color3	get_diffuse(t_vars *vars, t_light *light)
{
	t_vec3	light_dir;
	double	kd;

	light_dir = v_unit(v_minus(light->light_point, vars->rec.p));
	kd = fmax(v_dot(vars->rec.normal, light_dir), 0.0);
	return (vt_mul(light->r_rgb, kd));
}

t_vec3	get_reflect_vec(t_vec3 v, t_vec3 n)
{
	return (v_minus(v, vt_mul(n, v_dot(v, n) * 2)));
}

t_color3	get_specular(t_vars *vars, t_light *light)
{
	t_vec3	light_dir;
	t_vec3	view_dir;
	t_vec3	reflect_dir;
	double	spec;

	light_dir = v_unit(v_minus(light->light_point, vars->rec.p));
	view_dir = v_unit(vt_mul(vars->ray.dir, -1));
	reflect_dir = get_reflect_vec(vt_mul(light_dir, -1), vars->rec.normal);
	spec = pow(fmax(v_dot(view_dir, reflect_dir), 0.0), SHIN_VALUE);
	return (vt_mul(vt_mul(light->r_rgb, 0.5), spec));
}

t_color3	point_light_get(t_vars *vars, t_light *light)
{
	t_color3	diffuse;
	t_color3	specular;

	diffuse = get_diffuse(vars, light);
	specular = get_specular(vars, light);
	return (vt_mul(v_plus(v_plus(vars->ambient.r_rgb, diffuse), specular), light->brightness_ratio));
}

t_color3	execute_phong(t_vars *vars)
{
	t_color3	light_color;
	t_list		*light;

	light_color = color3(0, 0, 0);
	light = vars->light;
	while (light)
	{
		if (light->type == LIGHT)
			light_color = v_plus(light_color, point_light_get(vars, (t_light *)light->content));
		light = light->next;
	}
	return (v_min(v_mul(light_color, vars->rec.albedo), color3(1, 1, 1)));
}

t_color3	ray_color(t_vars *vars)
{
	t_vec3			unit_direction;
	double			a;

	vars->rec.tmin = 1e-6;
	vars->rec.tmax = INFINITY;
	if (hit(vars->objects, &vars->ray, &vars->rec))
		return (execute_phong(vars));
	unit_direction = v_unit(vars->ray.dir);
	a = 0.5 * (unit_direction.x + 1.0);
	return (v_plus(\
	vt_mul(color3(0.3, 0.3, 0.3), (1.0 - a)), \
	vt_mul(color3(0.1, 0.33, 0.3), a)));
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
