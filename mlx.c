/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:21:30 by sunko             #+#    #+#             */
/*   Updated: 2023/12/10 23:51:03 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#define WIDTH	960
#define HEIGHT	540

void	init_mlx(t_mlx_data *mlx_data)
{
	mlx_data->mlx = mlx_init();
	if (!mlx_data->mlx)
	{
		ft_putendl_fd("Error\nmlx_init", 2);
		exit(EXIT_FAILURE);
	}
	mlx_data->win = mlx_new_window(mlx_data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx_data->win)
	{
		ft_putendl_fd("Error\nmlx_new_window", 2);
		exit(EXIT_FAILURE);
	}
	mlx_data->img = mlx_new_image(mlx_data->mlx, WIDTH, HEIGHT);
	if (!mlx_data->img)
	{
		ft_putendl_fd("Error\nmlx_new_image", 2);
		exit(EXIT_FAILURE);
	}
	mlx_data->addr = mlx_get_data_addr(mlx_data->img, \
		&mlx_data->bits_per_pixel, &mlx_data->line_length, &mlx_data->endian);
	if (!mlx_data->addr)
	{
		ft_putendl_fd("Error\nmlx_get_data_addr", 2);
		exit(EXIT_FAILURE);
	}
}

static int	destroy_window(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
	mlx_destroy_window(mlx_data->mlx, mlx_data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	handle_key_press(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == 53)
		destroy_window(mlx_data);
	return (0);
}

void	execute_mlx(t_mlx_data *mlx_data)
{
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
	mlx_hook(mlx_data->win, ON_DESTROY, 0, destroy_window, mlx_data);
	mlx_hook(mlx_data->win, ON_KEYDOWN, 0, handle_key_press, mlx_data);
	mlx_loop(mlx_data->mlx);
}
