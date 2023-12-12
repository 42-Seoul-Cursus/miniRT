/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:38:16 by seunan            #+#    #+#             */
/*   Updated: 2023/12/12 16:48:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../structures.h"

enum	e_bool
{
	FALSE = 0,
	TRUE = 1
};

// parse.c
void	parse_rt(t_vars *vars, char *path);
double	parse_double(char **line);
t_vec3	parse_vec(char **line, enum e_bool is_endl);

// gen_env.c
void	gen_ambient(t_ambient *ambient, char *line);
void	gen_camera(t_camera *camera, char *line);
void	gen_light(t_light *light, char *line);

// gen_objs.c
void	gen_sphere(t_list **objects, char *line);
void	gen_plane(t_list **objects, char *line);
void	gen_cylinder(t_list **objects, char *line);

// check_env.c
void	check_ambient(t_ambient *ambient);
void	check_camera(t_camera *camera);
void	check_light(t_light *light);
int		check_range(double dst, double from, double to);
int		check_vec(t_vec3 vec, double from, double to, enum e_bool is_int);

// check_objs.c
void	check_sphere(t_sphere *sphere);
void	check_plane(t_plane *plane);
void	check_cylinder(t_cylinder *cylinder);

#endif
