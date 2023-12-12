/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:38:16 by seunan            #+#    #+#             */
/*   Updated: 2023/12/12 14:46:52 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define TRUE 1
# define FALSE 0

# include "../structures.h"

// parse.c
void	init_vars(t_vars *vars);
void	parse_rt(t_vars *vars, char *path);
double	parse_double(char **line);
t_vec3	parse_vec(char **line, int is_endl);

// gen_env.c
void	check_range(double dst, double from, double to);
void	check_rgb(t_color3 rgb);
void	gen_ambient(t_vars *vars, char *line);
void	gen_camera(t_vars *vars, char *line);
void	gen_light(t_vars *vars, char *line);

// gen_objs.c
void	gen_sphere(t_vars *vars, char *line);
void	gen_plane(t_vars *vars, char *line);
void	gen_cylinder(t_vars *vars, char *line);

#endif

