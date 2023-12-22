/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:12:43 by seunan            #+#    #+#             */
/*   Updated: 2023/12/22 14:03:47 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "structures.h"

// color.c
t_color3		get_color_int_to_real(t_color3 i_rgb);
t_color3		get_color_real_to_int(t_color3 r_rgb);
int				create_trgb(int t, t_color3 *color);
void			my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
unsigned int	extract_uv_color(t_mlx_data *data, int x, int y);

// mlx.c
void		reset_mlx(t_mlx_data *mlx_data);
void		execute_mlx(t_vars *vars);
void		init_mlx(t_mlx_data *mlx_data);

// world2view.c
void		world2view(t_vars *vars);
void		update_viewport(t_vars *vars);
void		rotate_object_and_light(t_vars *vars, t_4x4matrix rotate);
void		rotate_obj(t_list *cur, t_4x4matrix rotate, t_point3 view_point);
void		rotate_right(t_list *cur, t_4x4matrix rotate, t_point3 view_point);

// print.c
void		render(t_vars *vars);

#endif
