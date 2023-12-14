/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:48:16 by seunan            #+#    #+#             */
/*   Updated: 2023/12/13 23:02:27 by seunan           ###   ########.fr       */
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
	ESC = 53
};

void	move_front(t_mlx_args *mlx_args);
void	move_left(t_mlx_args *mlx_args);
void	move_back(t_mlx_args *mlx_args);
void	move_right(t_mlx_args *mlx_args);

#endif
