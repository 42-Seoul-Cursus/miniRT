/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 20:27:15 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray.h"
#include "utils.h"

static t_bool	hit_cone_body(t_cone *cone, t_ray *r, t_hit_record *rec);
static t_bool	has_real_roots(t_cone *cone, t_ray *r, \
	double *t_sm, double *t_lg);
static t_bool	is_point_on_cone(t_cone *cone, t_hit_record *rec, \
	t_point3 p, double t);
void			set_cone_normal(t_cone *cone, t_ray *r, t_hit_record *rec);

t_bool	hit_cone(t_cone *cone, t_ray *ray, t_hit_record *rec)
{
	t_bool			is_hit;
	t_hit_record	temp_rec;

	is_hit = FALSE;
	temp_rec = *rec;
	if (hit_disk(&(cone->bottom), cone->radius, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_cone_body(cone, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	return (is_hit);
}

static t_bool	hit_cone_body(t_cone *cone, t_ray *r, t_hit_record *rec)
{
	t_point3	p;
	double		t_sm;
	double		t_lg;

	if (!has_real_roots(cone, r, &t_sm, &t_lg))
		return (FALSE);
	if (t_sm > t_lg)
		swap_double(&t_sm, &t_lg);
	p = ray_at(r, t_sm);
	if (!is_point_on_cone(cone, rec, p, t_sm))
	{
		p = ray_at(r, t_lg);
		if (!is_point_on_cone(cone, rec, p, t_lg))
			return (FALSE);
		rec->t = t_lg;
		rec->color = cone->r_rgb;
		rec->p = p;
		set_cone_normal(cone, r, rec);
		return (TRUE);
	}
	rec->t = t_sm;
	rec->color = cone->r_rgb;
	rec->p = p;
	set_cone_normal(cone, r, rec);
	return (TRUE);
}

static t_bool	has_real_roots(t_cone *cone, t_ray *r, \
	double *t_sm, double *t_lg)
{
	double	a;
	double	b;
	double	c;
	double	oc;

	a = pow(cos(cone->half_angle), 2) * v_length2(v_minus(r->dir, vt_mul(\
		cone->normal_v, v_dot(r->dir, cone->normal_v)))) - pow(sin(\
		cone->half_angle), 2) * pow(v_dot(r->dir, cone->normal_v), 2);
	b = 2 * (pow(cos(cone->half_angle), 2) * v_dot(v_minus(r->dir, vt_mul(\
		cone->normal_v, v_dot(r->dir, cone->normal_v))), v_minus(v_minus(\
		r->orig, cone->apex), vt_mul(cone->normal_v, v_dot(v_minus(\
		r->orig, cone->apex), cone->normal_v)))) \
		- pow(sin(cone->half_angle), 2) * v_dot(r->dir, cone->normal_v) \
		* v_dot(v_minus(r->orig, cone->apex), cone->normal_v));
	c = pow(cos(cone->half_angle), 2) * v_length2(v_minus(v_minus(\
		r->orig, cone->apex), vt_mul(cone->normal_v, v_dot(v_minus(\
		r->orig, cone->apex), cone->normal_v)))) \
		- pow(sin(cone->half_angle), 2) * pow(v_dot(v_minus(\
		r->orig, cone->apex), cone->normal_v), 2);
	oc = b * b - 4 * a * c;
	if (oc <= 0 || a == 0)
		return (FALSE);
	*t_sm = (-b - sqrt(oc)) / (2 * a);
	*t_lg = (-b + sqrt(oc)) / (2 * a);
	return (TRUE);
}

static t_bool	is_point_on_cone(t_cone *cone, t_hit_record *rec, \
	t_point3 p, double t)
{
	if ((v_dot(cone->normal_v, v_minus(p, cone->bottom.point)) > 0 && \
		v_dot(cone->normal_v, v_minus(p, cone->apex)) < 0) && \
		(rec->tmin < t && t < rec->tmax))
		return (TRUE);
	return (FALSE);
}

void	set_cone_normal(t_cone *cone, t_ray *r, t_hit_record *rec)
{
	t_vec3	v;
	t_vec3	cp;

	cp = v_minus(rec->p, cone->apex);
	v = v_unit(v_minus(cone->center, cone->apex));
	rec->normal = v_unit(v_minus(cp, vt_mul(v, \
		(v_length2(cp) / v_dot(cp, v)))));
	if (v_dot(r->dir, rec->normal) >= 0)
		rec->normal = vt_mul(rec->normal, -1);
}
