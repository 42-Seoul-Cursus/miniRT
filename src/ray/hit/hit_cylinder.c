/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/19 11:33:35 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

static int	hit_cylinder_cap(t_plane *cap, double radius, t_ray *ray, t_vars *vars);
static int	hit_cylinder_body(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vars *vars)
{
	if (hit_cylinder_body(cylinder, ray, rec))
		return (1);
	if (hit_cylinder_cap(&cylinder->top, cylinder->radius, ray, vars))
		return (1);
	if (hit_cylinder_cap(&cylinder->bottom, cylinder->radius, ray, vars))
		return (1);
	return (0);
}

static int	hit_cylinder_body(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{

	/*
	p = ray->orig
	v = ray->dir
	p_a = cylinder->center
	v_a = cylinder->normal_v
	r = cylinder->radius
	*/

	// implement infinite cylinder
	t_point3 p = ray->orig;
	t_vec3 v = ray->dir;
	t_point3 p_a = cylinder->center;
	t_vec3 v_a = cylinder->normal_v;

	double	a;
	double	b;
	double	c;
	double	oc;

	t_vec3 x = v_minus(v, vt_mul(v_a, v_dot(v, v_a)));
	a = pow(v_length(x), 2);
	b = 2 * v_dot(x, v_minus(v_minus(p, p_a), vt_mul(v_a, v_dot(v_minus(p, p_a), v_a))));
	c = pow(v_length(v_minus(v_minus(p, p_a), vt_mul(v_a, v_dot(v_minus(p, p_a), v_a)))), 2) - pow(cylinder->radius, 2);
	oc = b * b - 4 * a * c;
	if (oc < 10e-4)
		return (0);

	/*
	p = ray->orig
	v = ray->dir
	p_a = cylinder->center
	v_a = cylinder->normal_v
	r = cylinder->radius
	q = p + vt
	*/

	// implement finite cylinder

	t_point3	q;
	double		t1;
	double		t2;
	double		t_sm;
	double		t_big;

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
	q = v_plus(ray->orig, vt_mul(ray->dir, t_sm));
	if (!(v_dot(v_a, v_minus(q, cylinder->bottom.point)) > 0 && v_dot(v_a, v_minus(q, cylinder->top.point)) < 0))
	{
		q = v_plus(ray->orig, vt_mul(ray->dir, t_sm));
		if (!(v_dot(v_a, v_minus(q, cylinder->bottom.point)) > 0 && v_dot(v_a, v_minus(q, cylinder->top.point)) < 0))
			return (0);
		else
		{
			rec->t = t_big;
			rec->color = cylinder->r_rgb;
			rec->p = ray_at(ray, t_big);
			rec->normal = cylinder->normal_v;
		}
	}
	rec->t = t_sm;
	rec->color = cylinder->r_rgb;
	rec->p = ray_at(ray, t_sm);
	rec->normal = cylinder->normal_v;
	return (1);
}

static int	hit_cylinder_cap(t_plane *cap, double radius, t_ray *ray, t_vars *vars)
{
	if (hit_plane(cap, ray, &vars->rec, vars))
	{
		t_point3	p = v_minus(vars->rec.p, cap->point);
		if (v_dot(cap->normal_v, p) != 0)
			return (0);
		if (v_dot(p, p) >= pow(radius, 2))
			return (0);
		vars->rec.color = cap->r_rgb;
		vars->rec.p = p;
		vars->rec.normal = cap->normal_v;
		return (1);
	}
	return (0);
}
