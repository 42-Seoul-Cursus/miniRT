/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:52:46 by sunko             #+#    #+#             */
/*   Updated: 2023/12/22 14:26:07 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "ray.h"
#include "render.h"

<<<<<<< HEAD
static t_color3	get_check_color(t_plane *plane, t_hit_record *rec, t_vars *var)
=======
static t_color3	set_uvmap_color(t_plane *plane, t_hit_record *rec)
>>>>>>> main
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

<<<<<<< HEAD
// static t_color3	get_uv_color(t_sphere *sphere, t_hit_record *rec)
// {

// }

int	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec, t_vars *vars)
=======
int	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
>>>>>>> main
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
	rec->normal = plane->normal_v;
	if (plane->checker == NULL)
		rec->color = plane->r_rgb;
	else
<<<<<<< HEAD
		rec->color = get_check_color(plane, rec, vars);
=======
		rec->color = set_uvmap_color(plane, rec);
>>>>>>> main
	rec->front_face = v_dot(ray->dir, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vt_mul(rec->normal, -1);
	return (1);
}
