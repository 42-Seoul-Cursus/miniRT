/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:21:30 by sunko             #+#    #+#             */
/*   Updated: 2023/12/14 23:52:13 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "hook.h"

void	init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
		ft_error("mlx_init");
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx_data->win)
		ft_error("mlx_new_window");
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	if (!mlx_data->img)
		ft_error("mlx_new_image");
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	if (!mlx_data->addr)
		ft_error("mlx_get_data_addr");
}

static int	destroy_window(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	handle_key_press(int keycode, t_mlx_args *mlx_args)
{
	if (keycode == ESC)
		destroy_window(mlx_args->mlx_data);
	if (keycode == FRONT)
		move_front(mlx_args);
	if (keycode == LEFT)
		move_left(mlx_args);
	if (keycode == BACK)
		move_back(mlx_args);
	if (keycode == RIGHT)
		move_right(mlx_args);
	if (keycode == ROTATE_UP)
		rotate_up(mlx_args);
	if (keycode == ROTATE_LEFT)
		rotate_left(mlx_args);
	if (keycode == ROTATE_DOWN)
		rotate_down(mlx_args);
	if (keycode == ROTATE_RIGHT)
		rotate_right(mlx_args);
	return (0);
}

void	execute_mlx(t_mlx_data *mlx_data, t_vars *vars)
{
	t_mlx_args	mlx_args;

	mlx_args.mlx_data = mlx_data;
	mlx_args.vars = vars;
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
	mlx_hook(mlx_data->win, ON_DESTROY, 0, destroy_window, mlx_data);
	mlx_hook(mlx_data->win, ON_KEYDOWN, 0, handle_key_press, &mlx_args);
	mlx_loop(mlx_data->mlx);
}
