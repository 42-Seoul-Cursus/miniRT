/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:48:16 by seunan            #+#    #+#             */
/*   Updated: 2023/12/14 23:02:26 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

enum e_keycode
{
	FRONT = 13,
	LEFT = 0,
	BACK = 1,
	RIGHT = 2,
	ROTATE_UP = 126,
	ROTATE_DOWN = 125,
	ROTATE_LEFT = 123,
	ROTATE_RIGHT = 124,
	ESC = 53
};

enum e_event
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

void	move_front(t_mlx_args *mlx_args);
void	move_left(t_mlx_args *mlx_args);
void	move_back(t_mlx_args *mlx_args);
void	move_right(t_mlx_args *mlx_args);
void	rotate_left(t_mlx_args *mlx_args);
void	rotate_right(t_mlx_args *mlx_args);
void	rotate_up(t_mlx_args *mlx_args);
void	rotate_down(t_mlx_args *mlx_args);

#endif
