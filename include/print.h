/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:12:43 by seunan            #+#    #+#             */
/*   Updated: 2023/12/14 20:22:56 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "structures.h"

// color.c
t_color3	get_color_int_to_real(t_color3 i_rgb);
t_color3	get_color_real_to_int(t_color3 r_rgb);
int			create_trgb(int t, t_color3 *color);
void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

// world2view.c
void		world2view(t_vars *vars);

void		render(t_vars *vars, t_mlx_data *mlx);

void		init_mlx(t_mlx_data *mlx_data);
void		execute_mlx(t_mlx_data *mlx_data, t_vars *vars);

#endif
