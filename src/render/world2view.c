/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world2view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 22:39:01 by sunko             #+#    #+#             */
/*   Updated: 2023/12/21 19:58:54 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "render.h"
#include "parse.h"

void	rotate_obj(t_list *cur, t_4x4matrix rotate, t_point3 view_point)
{
	if (cur->type == SPHERE)
		((t_sphere *)cur->content)->center = get_rotate_point(\
			((t_sphere *)cur->content)->center, view_point, rotate);
	else if (cur->type == PLANE)
	{
		((t_plane *)cur->content)->point = get_rotate_point(\
			((t_plane *)cur->content)->point, view_point, rotate);
		((t_plane *)cur->content)->normal_v = rotate_vec3(rotate, \
			((t_plane *)cur->content)->normal_v);
	}
	else if (cur->type == CYLINDER)
	{
		((t_cylinder *)cur->content)->center = get_rotate_point(\
			((t_cylinder *)cur->content)->center, view_point, rotate);
		((t_cylinder *)cur->content)->normal_v = rotate_vec3(rotate, \
			((t_plane *)cur->content)->normal_v);
		gen_cylinder_cap((t_cylinder *)cur->content);
	}
}

void	rotate_right(t_list *cur, t_4x4matrix rotate, t_point3 view_point)
{
	((t_light *)cur->content)->light_point = v_minus(\
			((t_light *)cur->content)->light_point, view_point);
	((t_light *)cur->content)->light_point = mv_mul(\
	rotate, vec4(((t_light *)cur->content)->light_point, 1));
}

void	rotate_object_and_light(t_vars *vars, t_4x4matrix rotate)
{
	t_list		*cur;

	cur = vars->objects;
	while (cur)
	{
		rotate_obj(cur, rotate, vars->camera.view_point);
		cur = cur->next;
	}
	cur = vars->light;
	while (cur)
	{
		rotate_right(cur, rotate, vars->camera.view_point);
		cur = cur->next;
	}
}

void	update_viewport(t_vars *vars)
{
	vars->camera.fov_len = 1 / tan((vars->camera.fov / 2) * (M_PI / 180));
	vars->camera.viewport_upper_left = v_minus(v_minus(v_minus(\
	vars->camera.view_point, vec3(0, 0, vars->camera.fov_len)) \
	, vt_mul(vars->camera.viewport_u, 0.5)) \
	, vt_mul(vars->camera.viewport_v, 0.5));
	vars->camera.pixel_00_loc = v_plus(\
	vars->camera.viewport_upper_left, vt_mul(\
	v_plus(vars->camera.pixel_delta_u, vars->camera.pixel_delta_v), 0.5));
}

/* 전체 씬을 카메라 뷰로 업데이트 */
void	world2view(t_vars *vars)
{
	t_4x4matrix	rotate_matrix;

	rotate_matrix = get_rotate_matrix(&vars->camera);
	rotate_object_and_light(vars, rotate_matrix);
	vars->camera.view_point = point3(0, 0, 0);
	vars->camera.direct_v = vec3(0, 0, -1);
	update_viewport(vars);
}
