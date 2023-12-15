/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:39:01 by sunko             #+#    #+#             */
/*   Updated: 2023/12/15 16:05:06 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

static t_4x4matrix	get_view_rotate_matrix(t_camera camera)
{
	t_4x4matrix	m;
	t_vec3		view_x;
	t_vec3		view_y;
	t_vec3		view_z;

	view_z = vt_mul(camera.direct_v, -1);
	if (camera.direct_v.y >= 1.0 - 10e-4 || camera.direct_v.y <= -1.0 + 10e-4)
		view_x = vec3(1.0, 0.0, 0.0);
	else
		view_x = v_unit(v_cross(view_z, vec3(0.0, 1.0, 0.0)));
	view_y = v_cross(view_z, view_x);
	m = _4x4matrix(vec4(view_x, 0.0), vec4(view_y, 0.0),
			vec4(view_z, 0.0), vec4(vec3(0.0, 0.0, 0.0), 1));
	return (m);
}

void	change_world2view_obj(t_list *cur,
	t_4x4matrix rotate, t_point3 view_point)
{
	if (cur->type == SPHERE)
	{
		((t_sphere *)cur->content)->center = \
			v_minus(((t_sphere *)cur->content)->center, view_point);
		((t_sphere *)cur->content)->center = \
			mv_mul(rotate, vec4(((t_sphere *)cur->content)->center, 1));
	}
	else if (cur->type == PLANE)
	{
		((t_plane *)cur->content)->point = \
			v_minus(((t_plane *)cur->content)->point, view_point);
		((t_plane *)cur->content)->normal_v = \
			mv_mul(rotate, vec4(((t_plane *)cur->content)->normal_v, 1));
	}
	else if (cur->type == CYLINDER)
	{
		((t_cylinder *)cur->content)->center = \
			v_minus(((t_cylinder *)cur->content)->center, view_point);
		((t_cylinder *)cur->content)->normal_v = \
			mv_mul(rotate, vec4(((t_cylinder *)cur->content)->normal_v, 1));
	}
}

void	rotate_object(t_vars *vars, t_4x4matrix rotate_matrix)
{
	t_list		*cur;
	t_4x4matrix	inverse_m;

	inverse_m = get_inverse_rotate_m(rotate_matrix);
	cur = vars->objects;
	while (cur)
	{
		change_world2view_obj(cur, inverse_m, vars->camera.view_point);
		cur = cur->next;
	}
	cur = vars->light;
	while (cur)
	{
		((t_light *)cur->content)->light_point = v_minus(\
			((t_light *)cur->content)->light_point, vars->camera.view_point);
		((t_light *)cur->content)->light_point = mv_mul(\
			inverse_m, vec4(((t_light *)cur->content)->light_point, 1));
		cur = cur->next;
	}
	vars->camera.view_point = point3(0, 0, 0);
	vars->camera.direct_v = mv_mul(\
	rotate_matrix, vec4(vars->camera.direct_v, 1));
}

void	update_viewport(t_vars *vars)
{
	vars->camera.fov_len = atan((vars->camera.fov / 2) * (M_PI / 180));
	vars->camera.viewport_upper_left = v_minus(v_minus(v_minus(\
	vars->camera.view_point, vec3(0, 0, vars->camera.fov_len)) \
	, vt_mul(vars->camera.viewport_u, 0.5)) \
	, vt_mul(vars->camera.viewport_v, 0.5));
	vars->camera.pixel_00_loc = v_plus(\
	vars->camera.viewport_upper_left \
	, vt_mul(\
	v_plus(vars->camera.pixel_delta_u, vars->camera.pixel_delta_v), 0.5));
}

void	world2view(t_vars *vars)
{
	t_4x4matrix	rotate_matrix;

	rotate_matrix = get_view_rotate_matrix(vars->camera);
	rotate_object(vars, rotate_matrix);
	update_viewport(vars);
}
