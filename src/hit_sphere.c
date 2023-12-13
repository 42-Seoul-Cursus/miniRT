/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:30:55 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 16:50:56 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
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
	if (b * b - a * c < 0 \
	|| update_nearest_hit_point(a, b, c, rec) == 0)
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
