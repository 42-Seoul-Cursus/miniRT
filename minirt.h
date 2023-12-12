/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:27:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 14:40:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structures.h"

void	init_mlx(t_mlx_data *mlx_data);
void	execute_mlx(t_mlx_data *mlx_data);

// utils.c
void	is_valid_arg(int ac, char *av[]);
void	init_vars(t_vars *vars);
void	is_valid_rt(t_vars *vars);

/* world2view */

// world2view.c
void	world2view(t_vars *vars);

#endif
