/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:27:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 12:43:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structures.h"

void		init_mlx(t_mlx_data *mlx_data);
void		execute_mlx(t_mlx_data *mlx_data);

// utils.c
void		is_valid_arg(int ac, char *av[]);
void		init_vars(t_vars *vars);
void		is_valid_rt(t_vars *vars);

// color.c
t_color3	get_color_int_to_real(t_color3 rgb);
t_color3	get_color_real_to_int(t_color3 rgb);

// world2view.c
void		world2view(t_vars *vars);

// render.c
void		render(t_vars *vars, t_mlx_data *mlx);
void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int			create_trgb(int t, t_color3 *color);

#endif
