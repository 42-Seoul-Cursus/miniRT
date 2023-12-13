/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:01:00 by seunan            #+#    #+#             */
/*   Updated: 2023/12/13 23:05:49 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "mlx.h"
#include "hook.h"

void	move_front(t_mlx_args *mlx_args)
{
	t_camera	camera;
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	camera = mlx_args->vars->camera;
	mlx_args->vars->camera.view_point = \
		v_plus(mlx_args->vars->camera.view_point, vec3(0, 0, 0.1));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_left(t_mlx_args *mlx_args)
{
	t_camera	camera;
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	camera = mlx_args->vars->camera;
	mlx_args->vars->camera.view_point = \
		v_plus(mlx_args->vars->camera.view_point, vec3(0.1, 0, 0));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_back(t_mlx_args *mlx_args)
{
	t_camera	camera;
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	camera = mlx_args->vars->camera;
	mlx_args->vars->camera.view_point = \
		v_minus(mlx_args->vars->camera.view_point, vec3(0, 0, 0.1));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_right(t_mlx_args *mlx_args)
{
	t_camera	camera;
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	camera = mlx_args->vars->camera;
	mlx_args->vars->camera.view_point = \
		v_minus(mlx_args->vars->camera.view_point, vec3(0.1, 0, 0));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
