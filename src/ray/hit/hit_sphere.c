/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:30:55 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 20:05:18 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>
#include "mlx.h"

/* P - C: 법선 벡터
정규화된 법선 벡터: (P - C) / r */

static t_bool	update_nearest_hit_point(double a, \
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
			return (FALSE);
	}
	rec->t = root;
	return (TRUE);
}

static t_color3	get_checkmap_color(t_sphere *sphere, t_hit_record *rec)
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

static t_color3	get_uv_color(t_sphere *sphere, t_hit_record *rec, t_uv_data *uv)
{
	double			u;
	double			v;
	unsigned int	color;
	t_color3		v_color;

	u = 1 - (atan2(rec->normal.x, rec->normal.z) / (2 * M_PI) + 0.5);
	v = 1 - acos(rec->normal.y / sphere->radius) / M_PI;
	color = extract_uv_color(uv, floor(u * uv->width), floor(v * uv->height));
	v_color = color3((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	return (get_color_int_to_real(v_color));
}

static t_vec3	get_bump_vector(t_color3 bump_color)
{
	t_vec3	bump_vec;

	bump_vec = v_unit(v_minus(vt_mul(bump_color, 2.0), vec3(1, 1, 1)));
	return (bump_vec);
}

t_bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;

	a = v_length2(ray->dir);
	b = v_dot(v_minus(ray->orig, sphere->center), ray->dir);
	c = v_length2(\
	v_minus(ray->orig, sphere->center)) - sphere->radius * sphere->radius;
	if (b * b - a * c < 0 || update_nearest_hit_point(a, b, c, rec) == 0)
		return (FALSE);
	rec->p = ray_at(ray, rec->t);
	rec->normal = v_unit(v_minus(rec->p, sphere->center));
	if (v_dot(ray->dir, rec->normal) > 0)
		rec->normal = vt_mul(rec->normal, -1);
	if (!sphere->checker && !sphere->uvmap)
		rec->color = sphere->r_rgb;
	else if (sphere->uvmap)
	{
		rec->color = get_uv_color(sphere, rec, sphere->uvmap->texture);
		rec->normal = mv_mul(get_orthogonal_basis(rec->normal), vec4(\
		get_bump_vector(get_uv_color(sphere, rec, sphere->uvmap->normal)), 1));
	}
	else if (sphere->checker)
		rec->color = get_checkmap_color(sphere, rec);
	return (TRUE);
}
