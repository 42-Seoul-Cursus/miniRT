/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:10:57 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 16:10:46 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "structures.h"

// v_utils.c
t_vec3		vec3(const double x, const double y, const double z);
t_point3	point3(const double x, const double y, const double z);
t_color3	color3(const double r, const double g, const double b);
void		set_vec(t_vec3 *vec, const double x, const double y,
				const double z);
void		set_color(t_color3 *color, const double r, const double g,
				const double v);
double		v_length2(const t_vec3 vec);
double		v_length(const t_vec3 vec);
t_vec3		v_plus(t_vec3 vec, const t_vec3 vec2);
t_vec3		vp_plus(t_vec3 vec, const double x, const double y, const double z);
t_vec3		v_minus(t_vec3 vec, const t_vec3 vec2);
t_vec3		vp_minus(t_vec3 vec, const double x, const double y,
				const double z);
t_vec3		vt_mul(t_vec3 vec, const double t);
t_vec3		v_mul(t_vec3 vec, const t_vec3 vec2);
t_vec3		vt_divide(t_vec3 vec, double t);
double		v_dot(t_vec3 vec, t_vec3 vec2);
t_vec3		v_cross(t_vec3 vec, t_vec3 vec2);
t_vec3		v_unit(t_vec3 vec);
t_vec4		vec4(t_vec3 v, const double w);
t_vec3		v_min(t_vec3 v1, t_vec3 v2);
t_vec3		rotate_vec3(t_4x4matrix rotate, t_vec3 vector);

// m_utils.c
t_4x4matrix	_4x4matrix(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4);
t_vec3		mv_mul(t_4x4matrix m, t_vec4 v);
t_4x4matrix	get_rotate_matrix(t_camera *camera);
t_4x4matrix	get_inverse_matrix(t_4x4matrix rotate);
t_4x4matrix	get_orthogonal_basis(t_vec3	v1);

// utils.c
void		is_valid_arg(int ac, char *av[]);
void		init_vars(t_vars *vars);

// rotate_utils.c
t_4x4matrix	get_inverse_matrix(t_4x4matrix rotate);
t_vec3		rotate_left_matrix(t_vec3 v);
t_vec3		rotate_right_matrix(t_vec3 v);
t_vec3		rotate_up_matrix(t_vec3 v);
t_vec3		rotate_down_matrix(t_vec3 v);
t_point3	get_rotate_point(t_point3 point, t_point3 view_point, \
	t_4x4matrix rotate);

#endif
