/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:27:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 11:40:24 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structures.h"

#define TRUE 1
#define FALSE 0

void	init_mlx(t_mlx_data *mlx_data);
void	execute_mlx(t_mlx_data *mlx_data);

/* parse */

// parse.c
void	init_vars(t_vars *vars);
void	parse_rt(t_vars *vars, char *path);
double	parse_double(char **line);
t_vec3	parse_vec(char **line, int is_endl);

// gen_env.c
void	gen_ambient(t_vars *vars, char *line);
void	gen_camera(t_vars *vars, char *line);
void	gen_light(t_vars *vars, char *line);

// gen_objs.c
void	gen_sphere(t_vars *vars, char *line);
void	gen_plane(t_vars *vars, char *line);
void	gen_cylinder(t_vars *vars, char *line);

// check_arg.c
void	is_valid_arg(int ac, char *av[]);

#endif
