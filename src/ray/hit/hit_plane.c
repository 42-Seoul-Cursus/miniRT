/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:52:46 by sunko             #+#    #+#             */
/*   Updated: 2023/12/21 14:57:05 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

static t_color3	set_uvmap_color(t_plane *plane, t_hit_record *rec, t_vars *var)
{
	t_vec3	e1;
	t_vec3	e2;

	e1 = v_unit(v_cross(plane->normal_v, vec3(1, 0, 0)));
	if (v_length(e1) == 0)
		e1 = v_unit(v_cross(plane->normal_v, vec3(0, 0, 1)));
	e2 = v_unit(v_cross(plane->normal_v, e1));
	if ((int)(floor(v_dot(e1, rec->p)) + floor(v_dot(e2, rec->p))) % 2 == 0)
		return (var->uvmap.rgb1);
	else
		return (var->uvmap.rgb2);
}

int	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec, t_vars *vars)
{
	double	denom;
	double	t;

	ray->dir = v_unit(ray->dir);
	denom = v_dot(plane->normal_v, ray->dir);
	if (fabs(denom) < 1e-6)
		return (0);
	t = v_dot(v_minus(plane->point, ray->orig), plane->normal_v) / denom;
	if (t < rec->tmin || t > rec->tmax)
		return (0);
	rec->t = t;
	rec->p = ray_at(ray, t);
	if (vars->uvmap.cnt == 0)
		rec->color = plane->r_rgb;
	else
		rec->color = set_uvmap_color(plane, rec, vars);
	rec->front_face = v_dot(ray->dir, rec->normal) < 0;
	rec->normal = plane->normal_v;
	if (!rec->front_face)
		rec->normal = vt_mul(rec->normal, -1);
	return (1);
}
