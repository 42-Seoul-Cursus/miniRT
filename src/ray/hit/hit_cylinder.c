/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 14:30:26 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "ray.h"

static int		hit_cylinder_body(\
				t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
static int		has_real_roots(t_cylinder *cy, t_ray *r, \
				double *t_sm, double *t_lg);
static int		is_point_on_cylinder(t_cylinder *cy, t_hit_record *rec, \
				t_point3 p, double t);
static t_vec3	get_cylinder_normal_v(t_cylinder *cy, t_ray *r, \
				t_hit_record *rec);

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	int				is_hit;
	t_hit_record	temp_rec;

	is_hit = 0;
	temp_rec = *rec;
	if (hit_cylinder_bottom(cylinder, ray, &temp_rec))
	{
		is_hit = 1;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_cylinder_top(cylinder, ray, &temp_rec))
	{
		is_hit = 1;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_cylinder_body(cylinder, ray, &temp_rec))
	{
		is_hit = 1;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	return (is_hit);
}

static int	hit_cylinder_body(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	t_point3	p;
	double		t_sm;
	double		t_lg;

	if (!has_real_roots(cy, r, &t_sm, &t_lg))
		return (0);
	p = ray_at(r, t_sm);
	if (!is_point_on_cylinder(cy, rec, p, t_sm))
	{
		p = ray_at(r, t_lg);
		if (!is_point_on_cylinder(cy, rec, p, t_lg))
			return (0);
		rec->t = t_lg;
		rec->color = cy->r_rgb;
		rec->p = p;
		rec->normal = get_cylinder_normal_v(cy, r, rec);
		return (1);
	}
	rec->t = t_sm;
	rec->color = cy->r_rgb;
	rec->p = p;
	rec->normal = get_cylinder_normal_v(cy, r, rec);
	return (1);
}

static int	has_real_roots(t_cylinder *cy, t_ray *r, \
	double *t_sm, double *t_lg)
{
	double	a;
	double	b;
	double	c;
	double	oc;

	a = v_length2(\
		v_minus(r->dir, vt_mul(cy->normal_v, v_dot(r->dir, cy->normal_v))));
	b = 2 * v_dot(v_minus(r->dir, vt_mul(cy->normal_v, v_dot(\
		r->dir, cy->normal_v))), v_minus(v_minus(r->orig, cy->center), vt_mul(\
		cy->normal_v, v_dot(v_minus(r->orig, cy->center), cy->normal_v))));
	c = v_length2(v_minus(v_minus(r->orig, cy->center), vt_mul(cy->normal_v, \
		v_dot(v_minus(r->orig, cy->center), cy->normal_v)))) \
		- pow(cy->radius, 2);
	oc = b * b - 4 * a * c;
	if (oc <= 0 || a == 0)
		return (0);
	*t_sm = (-b - sqrt(oc)) / (2 * a);
	*t_lg = (-b + sqrt(oc)) / (2 * a);
	if (*t_sm > *t_lg)
	{
		c = *t_lg;
		*t_lg = *t_sm;
		*t_sm = c;
	}
	return (1);
}

static int	is_point_on_cylinder(t_cylinder *cy, t_hit_record *rec, \
	t_point3 p, double t)
{
	if ((v_dot(cy->normal_v, v_minus(p, cy->bottom.point)) > 0 && \
		v_dot(cy->normal_v, v_minus(p, cy->top.point)) < 0) && \
		(rec->tmin < t && t < rec->tmax))
		return (1);
	return (0);
}

static	t_vec3	get_cylinder_normal_v(t_cylinder *cy, t_ray *r, \
		t_hit_record *rec)
{
	t_vec3	normal_v;

	normal_v = v_unit(v_minus(v_minus(rec->p, cy->center), vt_mul(\
		cy->normal_v, v_dot(cy->normal_v, v_minus(rec->p, cy->center)))));
	if (v_dot(r->dir, rec->normal) > 0)
		vt_mul(rec->normal, -1);
	return (normal_v);
}
