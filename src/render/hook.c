/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:45:56 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 16:34:57 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"
#include "hook.h"
#include "utils.h"
#include "mlx.h"
#include "parse.h"

static void	rotate_obj(t_list *cur, t_4x4matrix rotate, t_point3 view_point)
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

static void	rotate_object_and_light(\
	t_vars *vars, t_4x4matrix rotate_matrix, t_point3 view_point)
{
	t_list		*cur;

	cur = vars->objects;
	while (cur)
	{
		rotate_obj(cur, rotate_matrix, view_point);
		cur = cur->next;
	}
	cur = vars->light;
	while (cur)
	{
		((t_light *)cur->content)->light_point = \
			v_minus(((t_light *)cur->content)->light_point, view_point);
		((t_light *)cur->content)->light_point = mv_mul(\
			rotate_matrix, vec4(((t_light *)cur->content)->light_point, 1));
		cur = cur->next;
	}
}

static void	normalize_vector_space(t_vars *vars)
{
	t_4x4matrix	rotate_matrix;
	t_4x4matrix	inverse_matrix;

	rotate_matrix = get_rotate_matrix(&vars->camera);
	vars->camera.direct_v = vec3(0, 0, -1);
	inverse_matrix = get_inverse_matrix(rotate_matrix);
	rotate_object_and_light(vars, inverse_matrix, vars->camera.view_point);
	vars->camera.view_point = vec3(0, 0, 0);
	update_viewport(vars);
}

void	rotate_hook(t_vars *vars, int keycode)
{
	t_mlx_data	*mlx_data;

	mlx_data = &vars->mlx_data;
	reset_mlx(mlx_data);
	if (keycode == ROTATE_LEFT)
		vars->camera.direct_v = \
		v_unit(rotate_left_matrix(vars->camera.direct_v));
	else if (keycode == ROTATE_RIGHT)
		vars->camera.direct_v = \
		v_unit(rotate_right_matrix(vars->camera.direct_v));
	else if (keycode == ROTATE_UP)
		vars->camera.direct_v = \
		v_unit(rotate_up_matrix(vars->camera.direct_v));
	else if (keycode == ROTATE_DOWN)
		vars->camera.direct_v = \
		v_unit(rotate_down_matrix(vars->camera.direct_v));
	normalize_vector_space(vars);
	render(vars);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_hook(t_vars *vars, int keycode)
{
	t_mlx_data	*mlx_data;
	t_point3	prev_view_point;

	mlx_data = &vars->mlx_data;
	prev_view_point = vars->camera.view_point;
	if (keycode == FRONT)
		vars->camera.view_point = \
		v_plus(prev_view_point, vt_mul(vars->camera.direct_v, 3));
	else if (keycode == LEFT)
		vars->camera.view_point = \
		v_minus(prev_view_point, vt_mul(v_cross(\
		vars->camera.direct_v, vars->camera.up_v), 3));
	else if (keycode == BACK)
		vars->camera.view_point = \
		v_minus(prev_view_point, vt_mul(vars->camera.direct_v, 3));
	else if (keycode == RIGHT)
		vars->camera.view_point = \
		v_plus(prev_view_point, vt_mul(v_cross(\
		vars->camera.direct_v, vars->camera.up_v), 3));
	reset_mlx(mlx_data);
	update_viewport(vars);
	render(vars);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
