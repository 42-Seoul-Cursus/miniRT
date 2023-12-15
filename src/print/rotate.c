/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:45:56 by seunan            #+#    #+#             */
/*   Updated: 2023/12/16 01:20:44 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "hook.h"
#include "utils.h"
#include "mlx.h"
#include <math.h>

static t_vec3	rotate_vec3(t_4x4matrix rotate, t_vec3 vector)
{
	t_vec3 result;

	result.x = rotate.r1.x * vector.x + rotate.r1.y * vector.y + rotate.r1.z * vector.z;
	result.y = rotate.r2.x * vector.x + rotate.r2.y * vector.y + rotate.r2.z * vector.z;
	result.z = rotate.r3.x * vector.x + rotate.r3.y * vector.y + rotate.r3.z * vector.z;

	return (result);
}

void	change_obj(t_list *cur,
	t_4x4matrix rotate, t_point3 view_point)
{
	if (cur->type == SPHERE)
	{
		((t_sphere *)cur->content)->center = \
			mv_mul(rotate, vec4(((t_sphere *)cur->content)->center, 1));
	}
	else if (cur->type == PLANE)
	{
		((t_plane *)cur->content)->normal_v = rotate_vec3(rotate, ((t_plane *)cur->content)->normal_v);
		((t_plane *)cur->content)->point = \
			mv_mul(rotate, vec4(((t_plane *)cur->content)->point, 1));
	}
	else if (cur->type == CYLINDER)
	{
		((t_cylinder *)cur->content)->center = \
			v_minus(((t_cylinder *)cur->content)->center, view_point);
		((t_cylinder *)cur->content)->center = \
			mv_mul(rotate, vec4(((t_cylinder *)cur->content)->center, 1));
	}
}

static void	rotate_object1(t_vars *vars, t_4x4matrix rotate_matrix)
{
	t_list		*cur;

	cur = vars->objects;
	while (cur)
	{
		change_obj(cur, rotate_matrix, vars->camera.view_point);
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
}

static void	rotate_direct_v(t_vars *vars, t_4x4matrix rotate_matrix)
{
	vars->camera.direct_v = mv_mul(rotate_matrix, \
		vec4(vars->camera.direct_v, 1));
	vars->camera.direct_v = v_unit(vars->camera.direct_v);
}

static t_4x4matrix	get_view_rotate_matrix(t_camera *camera)
{
	t_4x4matrix	m;
	t_vec3		view_x;
	t_vec3		view_y;
	t_vec3		view_z;

	view_z = vt_mul(camera->direct_v, -1);
	if (camera->direct_v.y >= 1.0 - 10e-4 || camera->direct_v.y <= -1.0 + 10e-4)
		view_x = vec3(-1.0, 0.0, 0.0);
	else
		view_x = vt_mul(v_unit(v_cross(view_z, vec3(0.0, 1.0, 0.0))),-1);
	view_y = v_cross(view_z, view_x);
	m = _4x4matrix(vec4(view_x, 0.0), vec4(view_y, 0.0),
			vec4(view_z, 0.0), vec4(vec3(0.0, 0.0, 0.0), 1));
	return (m);
}

void	world2view1(t_vars *vars)
{
	t_4x4matrix	rotate_matrix;

	rotate_matrix = get_view_rotate_matrix(&vars->camera);
	rotate_direct_v(vars, rotate_matrix);
	rotate_matrix = get_inverse_rotate_m(rotate_matrix);
	rotate_object1(vars, rotate_matrix);
	update_viewport(vars);
}

t_vec3	rotate_left_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x * cos(0.1) + v.z * sin(0.1);
	v1.y = v.y;
	v1.z = -v.x * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_vec3	rotate_right_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x * cos(0.1) - v.z * sin(0.1);
	v1.y = v.y;
	v1.z = v.x * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_vec3	rotate_up_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x;
	v1.y = v.y * cos(0.1) - v.z * sin(0.1);
	v1.z = v.y * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_vec3	rotate_down_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x;
	v1.y = v.y * cos(0.1) + v.z * sin(0.1);
	v1.z = -v.y * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

void	rotate_left(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	mlx_args->vars->camera.direct_v = rotate_left_matrix(mlx_args->vars->camera.direct_v);
	mlx_args->vars->camera.direct_v = v_unit(mlx_args->vars->camera.direct_v);
	world2view1(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	rotate_right(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	mlx_args->vars->camera.direct_v = rotate_right_matrix(mlx_args->vars->camera.direct_v);
	mlx_args->vars->camera.direct_v = v_unit(mlx_args->vars->camera.direct_v);
	world2view1(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	rotate_up(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	mlx_args->vars->camera.direct_v = rotate_up_matrix(mlx_args->vars->camera.direct_v);
	mlx_args->vars->camera.direct_v = v_unit(mlx_args->vars->camera.direct_v);
	world2view1(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	rotate_down(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	mlx_args->vars->camera.direct_v = rotate_down_matrix(mlx_args->vars->camera.direct_v);
	mlx_args->vars->camera.direct_v = v_unit(mlx_args->vars->camera.direct_v);
	world2view1(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
