/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:27:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 23:53:06 by sunko            ###   ########.fr       */
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

// color.c
t_color3	get_color_int_to_real(t_color3 i_rgb);
t_color3	get_color_real_to_int(t_color3 r_rgb);

// world2view.c
void		world2view(t_vars *vars);

// render.c
void		render(t_vars *vars, t_mlx_data *mlx);
void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
int			create_trgb(int t, t_color3 *color);

// hit.c
int			hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec);

int			create_trgb(int t, t_color3 *color);
void		my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);

t_color3	execute_phong(t_vars *vars);
int			in_shadow(t_list *object, t_ray ray, double light_len);

#endif
