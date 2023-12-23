/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:38:16 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 20:01:16 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structures.h"

// parse.c
void			parse_rt(t_vars *vars, char *path);

// parse_utils.c
int				parse_int(char **line);
char			*parse_path(char **line);
double			parse_double(char **line);
t_vec3			parse_vec(char **line);

// check_utils.c
int				check_range(double dst, double from, double to);
int				check_vec(t_vec3 vec, double from, double to, t_bool is_int);

// check_map.c
void			check_map(t_vars *vars, void *content, \
					char *line, t_type type);

// check_env.c
void			check_ambient(t_ambient *ambient);
void			check_camera(t_camera *camera);
void			check_light(t_light *light);
void			check_uv_map(t_uv_map *uvmap);
void			check_checker_board(t_checker_map *checker);

// check_objs.c
void			check_sphere(t_sphere *sphere);
void			check_plane(t_plane *plane);
void			check_cylinder(t_cylinder *cylinder);
void			check_cone(t_cone *cone);
void			check_checker_board(t_checker_map *checker);

// gen_env.c
void			gen_ambient(t_ambient *ambient, char *line);
void			gen_camera(t_camera *camera, char *line);
void			gen_light(t_list **light, char *line);

// gen_objs.c
void			gen_sphere(t_vars *vars, char *line);
void			gen_plane(t_vars *vars, char *line);
void			gen_cylinder(t_vars *vars, char *line);
void			gen_cone(t_vars *vars, char *line);

// gen_objs_utils.c
void			gen_cylinder_cap(t_cylinder *cylinder, t_bool is_first);
void			gen_cone_cap(t_cone *cone, t_bool is_first);

#endif
