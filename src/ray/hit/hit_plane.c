/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:52:46 by sunko             #+#    #+#             */
/*   Updated: 2023/12/19 17:37:21 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "render.h"

// static t_color3	set_uvmap_color(t_plane *plane, t_hit_record *rec, t_vars *var)
// {
// 	t_vec3	e1;
// 	t_vec3	e2;

// 	e1 = v_unit(v_cross(plane->normal_v, vec3(1, 0, 0)));
// 	if (v_length(e1) == 0)
// 		e1 = v_unit(v_cross(plane->normal_v, vec3(0, 0, 1)));
// 	e2 = v_unit(v_cross(plane->normal_v, e1));
// 	if ((int)(floor(v_dot(e1, rec->p)) + floor(v_dot(e2, rec->p))) % 2 == 0)
// 		return (var->uvmap.rgb1);
// 	else
// 		return (var->uvmap.rgb2);
// }

#include <stdio.h>
static unsigned int	my_mlx_extract_texel(void *img, int x, int y)
{
	char		*dst;
	t_mlx_data	data;

	data.addr = mlx_get_data_addr(img, &data.bits_per_pixel,\
	&data.line_length, &data.endian);
	if (!data.addr)
		ft_error("mlx_get_data_addr");
	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static t_color3	set_map_rgb(t_vars *vars, t_plane *plane, t_hit_record *rec)
{
	t_vec3		u;
	t_vec3		v;
	t_vec3		uv_p;
	t_4x4matrix	rotate;

	u = v_unit(v_cross(plane->normal_v, vec3(1, 0, 0)));
	if (v_length(u) == 0)
		u = v_unit(v_cross(plane->normal_v, vec3(0, 0, 1)));
	v = v_unit(v_cross(plane->normal_v, u));
	rotate = _4x4matrix(vec4(u, 0), vec4(v, 0), vec4(plane->normal_v, 0), vec4(vec3(0, 0, 0), 1));
	uv_p = mv_mul(rotate, vec4(rec->p, 1));
	uv_p.x = fmod(uv_p.x, 8) / 8;
	uv_p.y = fmod(uv_p.y, 8) / 8;
	if (uv_p.x < 0)
		uv_p.x += 1;
	if (uv_p.y < 0)
		uv_p.y += 1;
	unsigned int color = my_mlx_extract_texel(vars->mlx_data.uv_img, floor(uv_p.x * vars->uvmap.width), floor(uv_p.y * vars->uvmap.height));
	return (color3((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF));
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
		rec->color = get_color_int_to_real(set_map_rgb(vars, plane, rec));
		// rec->color = set_uvmap_color(plane, rec, vars);
	rec->normal = plane->normal_v;
	return (1);
}
