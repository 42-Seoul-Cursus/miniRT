/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:39:01 by sunko             #+#    #+#             */
/*   Updated: 2023/12/15 23:06:24 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

static t_4x4matrix	get_view_rotate_matrix(t_camera *camera)
{
	t_4x4matrix	m;

	camera->view_z = vt_mul(camera->direct_v, -1);
	if (camera->direct_v.y >= 1.0 - 10e-4 || camera->direct_v.y <= -1.0 + 10e-4)
		camera->view_x = vec3(1.0, 0.0, 0.0);
	else
		camera->view_x = v_unit(v_cross(camera->view_z, vec3(0.0, 1.0, 0.0)));
	camera->view_y = v_cross(camera->view_z, camera->view_x);
	m = _4x4matrix(vec4(camera->view_x, 0.0), vec4(camera->view_y, 0.0),
			vec4(camera->view_z, 0.0), vec4(vec3(0.0, 0.0, 0.0), 1));
	return (m);
}

t_vec3	rotate_vec3(t_4x4matrix rotate, t_vec3 vector)
{
	t_vec3 result;

	result.x = rotate.r1.x * vector.x + rotate.r1.y * vector.y + rotate.r1.z * vector.z;
	result.y = rotate.r2.x * vector.x + rotate.r2.y * vector.y + rotate.r2.z * vector.z;
	result.z = rotate.r3.x * vector.x + rotate.r3.y * vector.y + rotate.r3.z * vector.z;

	return result;
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
		((t_plane *)cur->content)->point = \
			mv_mul(rotate, vec4(((t_plane *)cur->content)->point, 1));
		((t_plane *)cur->content)->normal_v = rotate_vec3(rotate, ((t_plane *)cur->content)->normal_v);
	}
	else if (cur->type == CYLINDER)
	{
		((t_cylinder *)cur->content)->center = \
			v_minus(((t_cylinder *)cur->content)->center, view_point);
		((t_cylinder *)cur->content)->center = \
			mv_mul(rotate, vec4(((t_cylinder *)cur->content)->center, 1));
	}
}

void	rotate_object(t_vars *vars, t_4x4matrix rotate_matrix)
{
	t_list		*cur;

	cur = vars->objects;
	while (cur)
	{
		change_world2view_obj(cur, rotate_matrix, vars->camera.view_point);
		cur = cur->next;
	}
	cur = vars->light;
	while (cur)
	{
		((t_light *)cur->content)->light_point = v_minus(\
			((t_light *)cur->content)->light_point, vars->camera.view_point);
		((t_light *)cur->content)->light_point = mv_mul(\
			rotate_matrix, vec4(((t_light *)cur->content)->light_point, 1));
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

	rotate_matrix = get_view_rotate_matrix(&vars->camera);
	rotate_object(vars, rotate_matrix);
	update_viewport(vars);
}
