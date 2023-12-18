/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:30:55 by sunko             #+#    #+#             */
/*   Updated: 2023/12/18 23:35:50 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>

static t_vec3	get_sphere_normal_v(t_sphere *sphere, t_hit_record *rec)
{
	t_vec3	normal_v;

	normal_v = v_unit(v_minus(rec->p, sphere->center));
	return (normal_v);
}

static int	update_nearest_hit_point(double a, \
double b, double c, t_hit_record *rec)
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

static t_color3	get_uvmap_color(t_sphere *sphere, t_hit_record *rec, t_uvmap *uv)
{
	t_vec3	d;
	double	theta;
	double	phi;
	double	u;
	double	v;

	d = v_unit(v_minus(rec->p, sphere->center));
	theta = atan2(d.x, d.z);
	phi = acos(d.y / sphere->radius);
	u = 1 - (theta / (2 * M_PI) + 0.5);
	v = 1 - phi / M_PI;
	if (((int)(floor(u * uv->width)) + (int)(floor(v * uv->height))) % 2 == 0)
		return (uv->rgb1);
	else
		return (uv->rgb2);
}

int	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec, t_uvmap *uv)
{
	double	a;
	double	b;
	double	c;

	a = v_length2(ray->dir);
	b = v_dot(v_minus(ray->orig, sphere->center), ray->dir);
	c = v_length2(\
	v_minus(ray->orig, sphere->center)) - sphere->radius * sphere->radius;
	if (b * b - a * c < 0 \
	|| update_nearest_hit_point(a, b, c, rec) == 0)
		return (0);
	rec->p = ray_at(ray, rec->t);
	rec->normal = get_sphere_normal_v(sphere, rec);
	if (uv->cnt == 0)
		rec->color = sphere->r_rgb;
	else
		rec->color = get_uvmap_color(sphere, rec, uv);
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
