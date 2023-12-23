/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 16:22:46 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "ray.h"

static int	is_point_on_cylinder(t_cylinder *cy, t_point3 p)
{
	if ((v_dot(cy->normal_v, v_minus(p, cy->bottom.point)) > 0 && \
		v_dot(cy->normal_v, v_minus(p, cy->top.point)) < 0))
		return (1);
	return (0);
}

static int	has_real_roots(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double	root;

	a = v_length2(\
		v_minus(r->dir, vt_mul(cy->normal_v, v_dot(r->dir, cy->normal_v))));
	b = v_dot(v_minus(r->dir, vt_mul(cy->normal_v, v_dot(\
		r->dir, cy->normal_v))), v_minus(v_minus(r->orig, cy->center), vt_mul(\
		cy->normal_v, v_dot(v_minus(r->orig, cy->center), cy->normal_v))));
	c = v_length2(v_minus(v_minus(r->orig, cy->center), vt_mul(cy->normal_v, \
		v_dot(v_minus(r->orig, cy->center), cy->normal_v)))) \
		- pow(cy->radius, 2);
	if (b * b - a * c < 0 || a == 0)
		return (0);
	root = (-b - sqrt(b * b - a * c)) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-b + sqrt(b * b - a * c)) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	rec->t = root;
	rec->p = ray_at(r, rec->t);
	return (1);
}

static t_vec3	get_cylinder_normal_v(t_cylinder *cy, t_ray *r, \
	t_hit_record *rec)
{
	t_vec3	normal_v;
	t_vec3	cp;

	cp = v_minus(rec->p, cy->center);
	normal_v = v_minus(cp, vt_mul(cy->normal_v, v_dot(cy->normal_v, cp)));
	normal_v = v_unit(normal_v);
	if (v_dot(r->dir, normal_v) > 0)
		vt_mul(normal_v, -1);
	return (normal_v);
}

static int	hit_cylinder_body(t_cylinder *cy, t_ray *r, t_hit_record *rec)
{
	if (!has_real_roots(cy, r, rec))
		return (0);
	rec->color = cy->r_rgb;
	rec->normal = get_cylinder_normal_v(cy, r, rec);
	if (!is_point_on_cylinder(cy, rec->p))
		return (0);
	return (1);
}

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
