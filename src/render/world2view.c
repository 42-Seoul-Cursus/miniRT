/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:39:01 by sunko             #+#    #+#             */
/*   Updated: 2023/12/18 13:25:12 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "render.h"

static void	world2view_obj(t_list *cur,
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
		((t_plane *)cur->content)->normal_v = rotate_vec3(rotate, \
		((t_plane *)cur->content)->normal_v);
	}
	else if (cur->type == CYLINDER)
	{
		((t_cylinder *)cur->content)->center = \
			v_minus(((t_cylinder *)cur->content)->center, view_point);
		((t_cylinder *)cur->content)->center = \
			mv_mul(rotate, vec4(((t_cylinder *)cur->content)->center, 1));
	}
}

static void	wolrd2view_light(\
	t_list *cur, t_4x4matrix rotate_matrix, t_point3 view_point)
{
	((t_light *)cur->content)->light_point = v_minus(\
			((t_light *)cur->content)->light_point, view_point);
	((t_light *)cur->content)->light_point = mv_mul(\
	rotate_matrix, vec4(((t_light *)cur->content)->light_point, 1));
}

static void	world2view_object_and_light(t_vars *vars, t_4x4matrix rotate_matrix)
{
	t_list		*cur;

	cur = vars->objects;
	while (cur)
	{
		world2view_obj(cur, rotate_matrix, vars->camera.view_point);
		cur = cur->next;
	}
	cur = vars->light;
	while (cur)
	{
		wolrd2view_light(cur, rotate_matrix, vars->camera.view_point);
		cur = cur->next;
	}
	vars->camera.view_point = point3(0, 0, 0);
	vars->camera.direct_v = vec3(0, 0, -1);
}

void	update_viewport(t_vars *vars)
{
	vars->camera.fov_len = 1 / tan((vars->camera.fov / 2) * (M_PI / 180));
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

	rotate_matrix = get_rotate_matrix(&vars->camera);
	world2view_object_and_light(vars, rotate_matrix);
	update_viewport(vars);
}
