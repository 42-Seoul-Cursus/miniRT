/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/18 15:11:27 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

static int	hit_cylinder_cap(t_plane *cap, double radius, t_ray *ray, t_hit_record *rec);
static int	hit_cylinder_body(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	if (hit_cylinder_body(cylinder, ray, rec))
		return (1);
	if (hit_cylinder_cap(&cylinder->top, cylinder->radius, ray, rec))
		return (1);
	if (hit_cylinder_cap(&cylinder->bottom, cylinder->radius, ray, rec))
		return (1);
	return (0);
}

static int	hit_cylinder_body(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double	oc;

	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	b = 2 * (ray->orig.x * ray->dir.x + ray->orig.z * ray->dir.z - \
		cylinder->center.x * ray->dir.x - cylinder->center.z * ray->dir.z);
	c = ray->orig.x * ray->orig.x + cylinder->center.x * cylinder->center.x + \
		ray->orig.z * ray->orig.z + cylinder->center.z * cylinder->center.z \
		- 2 * (ray->orig.x * cylinder->center.x + ray->orig.z * cylinder->center.z) \
		- cylinder->radius * cylinder->radius;
	oc = b * b - 4 * a * c;
	if (oc < 10e-4)
		return (0);

	double	t1;
	double	t2;
	double	t_sm;
	double	t_big;
	double	r_sm;
	double	r_big;

	t1 = (-b - sqrt(oc)) / (2 * a);
	t2 = (-b + sqrt(oc)) / (2 * a);
	if (t1 > t2)
	{
		t_sm = t2;
		t_big = t1;
	}
	else
	{
		t_sm = t1;
		t_big = t2;
	}
	r_sm = ray->orig.y + t_sm * ray->dir.y;
	r_big = ray->orig.y + t_big * ray->dir.y;
	if (!(cylinder->center.y - cylinder->height / 2 <= r_sm && r_sm <= cylinder->center.y + cylinder->height / 2))
	{
		if (!(cylinder->center.y - cylinder->height / 2 <= r_big && r_big <= cylinder->center.y + cylinder->height / 2))
		{
			return (0);
		}
		rec->t = t_big;
		rec->color = cylinder->r_rgb;
		rec->p = ray_at(ray, t_big);
		rec->normal = cylinder->normal_v;
		return (1);
	}
	rec->t = t_sm;
	rec->color = cylinder->r_rgb;
	rec->p = ray_at(ray, t_sm);
	rec->normal = cylinder->normal_v;
	return (1);
}

static int	hit_cylinder_cap(t_plane *cap, double radius, t_ray *ray, t_hit_record *rec)
{
	if (hit_plane(cap, ray, rec))
	{
		t_vec3	p = v_plus(ray->orig, vt_mul(ray->dir, rec->t));
		t_vec3	v = v_minus(p, cap->point);
		double	d2 = v_dot(v, v);
		if (sqrt(d2) > radius)
			return (0);
		rec->color = cap->r_rgb;
		rec->p = p;
		rec->normal = cap->normal_v;
		return (1);
	}
	return (0);
}