/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:52:46 by sunko             #+#    #+#             */
/*   Updated: 2023/12/20 15:23:28 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "render.h"

// static t_color3	get_check_color(t_plane *plane, t_hit_record *rec, t_vars *var)
// {
// 	t_vec3	e1;
// 	t_vec3	e2;

// 	e1 = vec4_to_vec3(plane->normal_v_basis.r1);
// 	e2 = vec4_to_vec3(plane->normal_v_basis.r2);
// 	if ((int)(floor(v_dot(e1, rec->p)) + floor(v_dot(e2, rec->p))) % 2 == 0)
// 		return (var->uvmap.rgb1);
// 	else
// 		return (var->uvmap.rgb2);
// }

static unsigned int	extract_uv_color(t_mlx_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + y * data->line_length + x * data->bits_per_pixel / 8;
	return (*(unsigned int *)dst);
}

static t_color3	get_uv_map_color
	(t_vars *vars, t_plane *plane, t_hit_record *rec, t_mlx_data *data)
{
	t_point3	uv_p;
	t_vec3		v_color;
	unsigned	color;


	uv_p = mv_mul(plane->normal_v_basis, vec4(rec->p, 1));
	uv_p.x = fmod(uv_p.x, 8) / 8;
	uv_p.y = fmod(uv_p.y, 8) / 8;
	if (uv_p.x < 0)
		uv_p.x += 1;
	if (uv_p.y < 0)
		uv_p.y += 1;
	color = extract_uv_color(data,\
	floor(uv_p.x * vars->uvmap.width), floor(uv_p.y * vars->uvmap.height));
	v_color = color3((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
	return (get_color_int_to_real(v_color));
}

#include <stdio.h>
int	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec, t_vars *vars)
{
	double		denom;
	double		t;
	t_vec3		bump_color;

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
	{
		rec->color = get_uv_map_color(vars, plane, rec, &vars->uvmap.texture);
		bump_color = get_uv_map_color(vars, plane, rec, &vars->uvmap.normal);
		rec->normal = v_unit(v_minus(vt_mul(bump_color, 2.0), vec3(1, 1, 1)));
	}
	/*
	checker borad logic
		rec->color = get_check_color(plane, rec, vars);
		rec->normal = plane->normal_v;
	*/
	return (1);
}
