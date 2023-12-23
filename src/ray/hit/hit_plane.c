/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:52:46 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 20:04:25 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "ray.h"
#include "render.h"

static t_color3	get_checkmap_color(t_plane *plane, t_hit_record *rec)
{
	t_vec3	e1;
	t_vec3	e2;

	e1 = v_unit(v_cross(plane->normal_v, vec3(1, 0, 0)));
	if (v_length(e1) == 0)
		e1 = v_unit(v_cross(plane->normal_v, vec3(0, 0, 1)));
	e2 = v_unit(v_cross(plane->normal_v, e1));
	if ((int)(floor(v_dot(e1, rec->p)) + floor(v_dot(e2, rec->p))) % 2 == 0)
		return (get_color_int_to_real(plane->checker->rgb1));
	else
		return (get_color_int_to_real(plane->checker->rgb2));
}

static t_color3	get_uv_color(t_plane *plane, t_hit_record *rec, t_uv_data *uv)
{
	t_point3		uv_p;
	t_color3		v_color;
	unsigned int	color;

	uv_p = mv_mul(plane->normal_v_basis, vec4(rec->p, 1));
	uv_p.x = fmod(uv_p.x, 8) / 8;
	uv_p.y = fmod(uv_p.y, 8) / 8;
	if (uv_p.x < 0)
		uv_p.x += 1;
	if (uv_p.y < 0)
		uv_p.y += 1;
	color = extract_uv_color(uv, \
	floor(uv_p.x * uv->width), floor(uv_p.y * uv->height));
	v_color = color3((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	return (get_color_int_to_real(v_color));
}

static t_vec3	get_bump_vector(t_color3 bump_color)
{
	t_vec3	bump_vector;

	bump_vector = v_minus(vt_mul(bump_color, 2.0), vec3(1, 1, 1));
	return (v_unit(bump_vector));
}

t_bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double	denom;
	double	t;

	denom = v_dot(plane->normal_v, ray->dir);
	if (fabs(denom) < 1e-6)
		return (FALSE);
	t = v_dot(v_minus(plane->point, ray->orig), plane->normal_v) / denom;
	if (t < rec->tmin || t > rec->tmax)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = plane->normal_v;
	if (v_dot(ray->dir, rec->normal) > 0)
		rec->normal = vt_mul(rec->normal, -1);
	if (!plane->checker && !plane->uvmap)
		rec->color = plane->r_rgb;
	else if (plane->uvmap)
	{
		rec->color = get_uv_color(plane, rec, plane->uvmap->texture);
		rec->normal = mv_mul(get_orthogonal_basis(rec->normal), vec4(\
		get_bump_vector(get_uv_color(plane, rec, plane->uvmap->normal)), 1));
	}
	else if (plane->checker)
		rec->color = get_checkmap_color(plane, rec);
	return (TRUE);
}
