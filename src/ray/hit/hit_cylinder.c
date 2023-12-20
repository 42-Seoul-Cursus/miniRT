/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 00:06:10 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

static int	hit_cylinder_cap(\
	t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vars *vars);
static int	hit_cylinder_body(\
	t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vars *vars)
{
	if (hit_cylinder_body(cylinder, ray, rec))
		return (1);
	if (hit_cylinder_cap(cylinder, ray, rec, vars))
		return (1);
	return (0);
}

static int	hit_cylinder_body(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	// implement infinite cylinder

	double	a;
	double	b;
	double	c;
	double	oc;

	t_vec3	x = v_minus(r->dir, vt_mul(cy->normal_v, v_dot(r->dir, cy->normal_v)));
	a = v_length2(x);
	b = 2 * v_dot(x, v_minus(v_minus(r->orig, cy->center), vt_mul(cy->normal_v, v_dot(v_minus(r->orig, cy->center), cy->normal_v))));
	c = v_length2(v_minus(v_minus(r->orig, cy->center), vt_mul(cy->normal_v, v_dot(v_minus(r->orig, cy->center), cy->normal_v)))) - pow(cy->radius, 2);
	oc = b * b - 4 * a * c;
	if (oc <= 0)
		return (0);

	// implement finite cylinder

	t_point3	p;
	double		t_sm;
	double		t_lg;
	double		tmp;

	t_sm = (-b - sqrt(oc)) / (2 * a);
	t_lg = (-b + sqrt(oc)) / (2 * a);
	if (t_sm > t_lg)
	{
		tmp = t_lg;
		t_lg = t_sm;
		t_sm = tmp;
	}
	p = ray_at(r, t_sm);
	if (!(v_dot(cy->normal_v, v_minus(p, cy->bottom.point)) > 0 && v_dot(cy->normal_v, v_minus(p, cy->top.point)) < 0) || !(rec->tmin < t_sm && t_sm < rec->tmax))
	{
		p = ray_at(r, t_lg);
		if (!(v_dot(cy->normal_v, v_minus(p, cy->bottom.point)) > 0 && v_dot(cy->normal_v, v_minus(p, cy->top.point)) < 0) || !(rec->tmin < t_lg && t_lg < rec->tmax))
			return (0);
		rec->t = t_lg;
		rec->color = cy->r_rgb;
		rec->p = p;
		rec->normal = v_unit(v_minus(v_minus(p, cy->center), vt_mul(cy->normal_v, v_dot(cy->normal_v, v_minus(p, cy->center)))));
		if (v_dot(rec->normal, r->dir) > 0)
			rec->normal = v_minus(rec->normal, vec3(-1, -1, -1));
		return (1);
	}
	rec->t = t_sm;
	rec->color = cy->r_rgb;
	rec->p = p;
	rec->normal = v_unit(v_minus(v_minus(p, cy->center), vt_mul(cy->normal_v, v_dot(cy->normal_v, v_minus(p, cy->center)))));
	if (v_dot(rec->normal, r->dir) > 0)
		rec->normal = v_minus(rec->normal, vec3(-1, -1, -1));
	return (1);
}

static int	hit_cylinder_cap(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vars *vars)
{
	t_plane		cap;
	t_point3	p;
	double		radius;

	radius = cylinder->radius;
	cap = cylinder->top;
	if (hit_plane(&cap, ray, rec, vars))
	{
		p = v_minus(rec->p, cap.point);
		if (v_dot(p, p) < radius * radius)
			return (1);
	}
	cap = cylinder->bottom;
	if (hit_plane(&cap, ray, rec, vars))
	{
		p = v_minus(rec->p, cap.point);
		if (v_dot(p, p) < radius * radius)
			return (1);
	}
	return (0);
}
