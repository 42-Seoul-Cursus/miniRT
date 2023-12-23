/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 22:16:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "ray.h"

static t_bool	hit_cylinder_body(\
				t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
static t_bool	has_real_roots(t_cylinder *cy, t_ray *r, \
				double *t_sm, double *t_lg);
static t_bool	is_point_on_cylinder(t_cylinder *cy, t_hit_record *rec, \
				t_point3 p, double t);
static void		set_cylinder_normal(t_cylinder *cy, t_ray *r, \
				t_hit_record *rec);

t_bool	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	t_bool			is_hit;
	t_hit_record	temp_rec;

	is_hit = FALSE;
	temp_rec = *rec;
	if (hit_disk((&cylinder->top), cylinder->radius, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_disk((&cylinder->bottom), cylinder->radius, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_cylinder_body(cylinder, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	return (is_hit);
}

static t_bool	hit_cylinder_body(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	t_point3	p;
	double		t_sm;
	double		t_lg;

	if (!has_real_roots(cy, r, &t_sm, &t_lg))
		return (FALSE);
	if (t_sm > t_lg)
		swap_double(&t_sm, &t_lg);
	p = ray_at(r, t_sm);
	if (!is_point_on_cylinder(cy, rec, p, t_sm))
	{
		p = ray_at(r, t_lg);
		if (!is_point_on_cylinder(cy, rec, p, t_lg))
			return (FALSE);
		rec->t = t_lg;
		rec->color = cy->r_rgb;
		rec->p = p;
		set_cylinder_normal(cy, r, rec);
		return (TRUE);
	}
	rec->t = t_sm;
	rec->color = cy->r_rgb;
	rec->p = p;
	set_cylinder_normal(cy, r, rec);
	return (TRUE);
}

static t_bool	has_real_roots(t_cylinder *cy, t_ray *r, \
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
		return (FALSE);
	*t_sm = (-b - sqrt(oc)) / (2 * a);
	*t_lg = (-b + sqrt(oc)) / (2 * a);
	return (TRUE);
}

static t_bool	is_point_on_cylinder(t_cylinder *cy, t_hit_record *rec, \
	t_point3 p, double t)
{
	if ((v_dot(cy->normal_v, v_minus(p, cy->bottom.point)) > 0 && \
		v_dot(cy->normal_v, v_minus(p, cy->top.point)) < 0) && \
		(rec->tmin < t && t < rec->tmax))
		return (TRUE);
	return (FALSE);
}

static void	set_cylinder_normal(t_cylinder *cy, t_ray *r, \
		t_hit_record *rec)
{
	rec->normal = v_unit(v_minus(v_minus(rec->p, cy->center), vt_mul(\
		cy->normal_v, v_dot(cy->normal_v, v_minus(rec->p, cy->center)))));
	rec->front_face = v_dot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vt_mul(rec->normal, -1);
}
