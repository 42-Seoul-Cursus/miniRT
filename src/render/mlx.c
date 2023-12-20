/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:21:30 by sunko             #+#    #+#             */
/*   Updated: 2023/12/19 22:19:47 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "libft.h"
#include "hook.h"
#include "render.h"

void	reset_mlx(t_mlx_data *mlx_data)
{
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	if (!mlx_data->img)
		ft_error("mlx_new_image");
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	if (!mlx_data->addr)
		ft_error("mlx_get_data_addr");
}

void	init_mlx(t_vars *vars)
{
	vars->mlx_data.mlx = mlx_init();
	if (!vars->mlx_data.mlx)
		ft_error("mlx_init");
	vars->mlx_data.win = \
	mlx_new_window(vars->mlx_data.mlx, WIDTH, HEIGHT, "miniRT");
	if (!vars->mlx_data.win)
		ft_error("mlx_new_window");
	vars->mlx_data.img = mlx_new_image(vars->mlx_data.mlx, WIDTH, HEIGHT);
	vars->uvmap.texture.img = \
	mlx_xpm_file_to_image(vars->mlx_data.mlx,\
	 "./maps/brick.xpm", &vars->uvmap.width, &vars->uvmap.height);
	vars->uvmap.normal.img = \
	mlx_xpm_file_to_image(vars->mlx_data.mlx,\
	 "./maps/brick_normal.xpm", &vars->uvmap.width, &vars->uvmap.height);
	if (!vars->mlx_data.img || !vars->uvmap.texture.img)
		ft_error("mlx_new_image");
	vars->mlx_data.addr = \
	mlx_get_data_addr(vars->mlx_data.img, &vars->mlx_data.bits_per_pixel, \
	&vars->mlx_data.line_length, &vars->mlx_data.endian);
	vars->uvmap.texture.addr = \
	mlx_get_data_addr(vars->uvmap.texture.img, &vars->uvmap.texture.bits_per_pixel, \
	&vars->uvmap.texture.line_length, &vars->uvmap.texture.endian);
	vars->uvmap.normal.addr = mlx_get_data_addr(vars->uvmap.normal.img, &vars->uvmap.normal.bits_per_pixel, \
	&vars->uvmap.normal.line_length, &vars->uvmap.normal.endian);
	if (!vars->mlx_data.addr || !vars->uvmap.texture.addr || !vars->uvmap.normal.addr)
		ft_error("mlx_get_data_addr");
}

static int	destroy_window(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	handle_key_press(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		destroy_window(&vars->mlx_data);
	if (keycode == FRONT || (keycode >= LEFT && keycode <= RIGHT))
		move_hook(vars, keycode);
	if (keycode >= ROTATE_LEFT && keycode <= ROTATE_UP)
		rotate_hook(vars, keycode);
	return (0);
}

void	execute_mlx(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx_data.mlx,\
	vars->mlx_data.win, vars->mlx_data.img, 0, 0);
	mlx_hook(vars->mlx_data.win, ON_DESTROY, 0, destroy_window, &vars->mlx_data);
	mlx_hook(vars->mlx_data.win, ON_KEYDOWN, 0, handle_key_press, vars);
	mlx_loop(vars->mlx_data.mlx);
}
