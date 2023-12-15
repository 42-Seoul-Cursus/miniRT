/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:01:00 by seunan            #+#    #+#             */
/*   Updated: 2023/12/15 23:37:21 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"
#include "hook.h"
#include "print.h"

/*
카메라의 방향 벡터(0,0,-1)
카메라의 업 벡터 (0,1,0)
업벡터와 방향벡터의 외적을 구하면 오른쪽 벡터가 나온다.

lookat 행렬
mat4 view를 만들어서
view.x = right vector
view.y = up vector
view.z = dir vector
view.w = camera position vector
*/

#include <stdio.h>
void	move_front(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_args->vars->camera.view_point = \
		v_plus(mlx_args->vars->camera.view_point, vt_mul(mlx_args->vars->camera.direct_v, 3));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	update_viewport(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_left(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_args->vars->camera.view_point = \
		v_minus(mlx_args->vars->camera.view_point, vt_mul(v_cross(mlx_args->vars->camera.direct_v, mlx_args->vars->camera.up_v), 3));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	update_viewport(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_back(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	// 카메라 위치 = 카메라 위치 + 카메라 스피드 * 카메라 방향 벡터
	mlx_args->vars->camera.view_point = \
		v_minus(mlx_args->vars->camera.view_point, vt_mul(mlx_args->vars->camera.direct_v, 3));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	update_viewport(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

void	move_right(t_mlx_args *mlx_args)
{
	t_mlx_data	*mlx_data;

	mlx_data = mlx_args->mlx_data;
	mlx_args->vars->camera.view_point = \
		v_plus(mlx_args->vars->camera.view_point, vt_mul(v_cross(mlx_args->vars->camera.direct_v, mlx_args->vars->camera.up_v), 3));
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	update_viewport(mlx_args->vars);
	render(mlx_args->vars, mlx_data);
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
