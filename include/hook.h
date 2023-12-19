/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:48:16 by seunan            #+#    #+#             */
/*   Updated: 2023/12/19 11:14:20 by sunko            ###   ########.fr       */
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

void	reset_mlx(t_mlx_data *mlx_data);
void	rotate_hook(t_vars *vars, int keycode);
void	move_hook(t_vars *vars, int keycode);

#endif
