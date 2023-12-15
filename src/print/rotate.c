/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:45:56 by seunan            #+#    #+#             */
/*   Updated: 2023/12/15 21:11:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "hook.h"
#include "utils.h"
#include "mlx.h"

void	rotate_object1(t_vars *vars, t_4x4matrix rotate_matrix)
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
	inverse_m, vec4(vars->camera.direct_v, 1));
}

void	rotate_world2view(t_vars *vars, double angle_x, double angle_y)
{
	t_4x4matrix	rotate_matrix;

	rotate_matrix = create_view_matrix(vars->camera, angle_x, angle_y);
	rotate_object1(vars, rotate_matrix);
	update_viewport(vars);
}

void	rotate_left(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	rotate_world2view(mlx_args->vars, -0.1, 0);
	update_viewport(mlx_args->vars);
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
	rotate_world2view(mlx_args->vars, 0.1, 0);
	update_viewport(mlx_args->vars);
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
	rotate_world2view(mlx_args->vars, 0, 0.1);
	update_viewport(mlx_args->vars);
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
	rotate_world2view(mlx_args->vars, 0, -0.1);
	update_viewport(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
