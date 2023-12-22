/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:30:55 by sunko             #+#    #+#             */
/*   Updated: 2023/12/21 23:26:13 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>

/* P - C: 법선 벡터
정규화된 법선 벡터: (P - C) / r */
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

static t_color3	get_uvmap_color(t_sphere *sphere, t_hit_record *rec)
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
	if (((int)(floor(u * sphere->checker->width)) \
		+ (int)(floor(v * sphere->checker->height))) % 2 == 0)
		return (get_color_int_to_real(sphere->checker->rgb1));
	else
		return (get_color_int_to_real(sphere->checker->rgb2));
}

int	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;

	a = v_length2(ray->dir);
	b = v_dot(v_minus(ray->orig, sphere->center), ray->dir);
	c = v_length2(\
	v_minus(ray->orig, sphere->center)) - sphere->radius * sphere->radius;
	if (b * b - a * c < 0 || update_nearest_hit_point(a, b, c, rec) == 0)
		return (0);
	rec->p = ray_at(ray, rec->t);
	rec->normal = get_sphere_normal_v(sphere, rec);
	if (sphere->checker == NULL)
		rec->color = sphere->r_rgb;
	else
		rec->color = get_uvmap_color(sphere, rec);
	rec->front_face = v_dot(ray->dir, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vt_mul(rec->normal, -1);
	return (1);
}
