/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/18 23:36:20 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>

int	hit_obj(t_list *object, t_ray *ray, t_hit_record *rec, t_uvmap *uv)
{
	int		is_hit;

	is_hit = 0;
	if (object->type == SPHERE)
		is_hit = hit_sphere((t_sphere *)object->content, ray, rec, uv);
	else if (object->type == PLANE)
		is_hit = hit_plane((t_plane *)object->content, ray, rec);
	else if (object->type == CYLINDER)
		is_hit = hit_cylinder((t_cylinder *)object->content, ray, rec);
	return (is_hit);
}

int	hit(t_vars *vars, t_ray *ray, t_hit_record *rec)
{
	int				is_hit;
	t_list			*obj;
	t_hit_record	temp_rec;

	is_hit = 0;
	temp_rec = *rec;
	obj = vars->objects;
	while (obj)
	{
		if (hit_obj(obj, ray, &temp_rec))
		{
			is_hit = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		obj = obj->next;
	}
	return (is_hit);
}

int	in_shadow(t_vars *vars, t_ray r, double light_len)
{
	t_hit_record	rec;
	t_ray			correct_ray;

	rec.tmin = 1e-6;
	rec.tmax = light_len;
	correct_ray = ray(v_plus(r.orig, vt_mul(r.dir, 10)), r.dir);
	if (hit(vars, &correct_ray, &rec))
	{
		return (1);
	}
	return (0);
}

t_color3	ray_color(t_vars *vars)
{
	vars->rec.tmin = 1e-6;
	vars->rec.tmax = INFINITY;
	if (hit(vars, &vars->ray, &vars->rec))
		return (execute_phong(vars));
	return (color3(0.9, 0.9, 0.9));
}
/* int	hit_obj(t_list *object, t_ray *ray, t_hit_record *rec)
{
	int		is_hit;

	is_hit = 0;
	if (object->type == SPHERE)
		is_hit = hit_sphere((t_sphere *)object->content, ray, rec);
	else if (object->type == PLANE)
		is_hit = hit_plane((t_plane *)object->content, ray, rec);
	else if (object->type == CYLINDER)
		is_hit = hit_cylinder((t_cylinder *)object->content, ray, rec);
	return (is_hit);
}

int	hit(t_list *objects, t_ray *ray, t_hit_record *rec, t_uvmap *uv)
{
	int				is_hit;
	t_hit_record	temp_rec;

	is_hit = 0;
	temp_rec = *rec;
	while (objects)
	{
		if (hit_obj(objects, ray, &temp_rec, uv))
		{
			is_hit = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		objects = objects->next;
	}
	return (is_hit);
}

int	in_shadow(t_list *object, t_ray r, double light_len)
{
	t_hit_record	rec;
	t_ray			correct_ray;
	rec.tmin = 1e-6;
	rec.tmax = light_len;

	correct_ray = ray(v_plus(r.orig, vt_mul(r.dir, 7)), r.dir);
	if (hit(object, &correct_ray, &rec))
	{
		return (1);
	}
	return (0);
}

t_color3	ray_color(t_vars *vars)
{
	vars->rec.tmin = 1e-6;
	vars->rec.tmax = INFINITY;
	if (hit(vars->objects, &vars->ray, &vars->rec, &vars->uvmap))
		return (execute_phong(vars));
	return (color3(0.9, 0.9, 0.9));
}
 */
