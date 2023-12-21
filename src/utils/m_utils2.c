/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:09:26 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 16:35:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structures.h"
#include "utils.h"

t_vec3	rotate_left_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x * cos(0.1) - v.z * sin(0.1);
	v1.y = v.y;
	v1.z = v.x * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_vec3	rotate_right_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x * cos(0.1) + v.z * sin(0.1);
	v1.y = v.y;
	v1.z = -v.x * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_vec3	rotate_up_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x;
	v1.y = v.y * cos(0.1) - v.z * sin(0.1);
	v1.z = v.y * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_vec3	rotate_down_matrix(t_vec3 v)
{
	t_vec3		v1;

	v1.x = v.x;
	v1.y = v.y * cos(0.1) + v.z * sin(0.1);
	v1.z = -v.y * sin(0.1) + v.z * cos(0.1);
	return (v1);
}

t_point3	get_rotate_point(t_point3 point, t_point3 view_point, \
	t_4x4matrix rotate)
{
	t_point3	out;

	out = point;
	out = v_minus(out, view_point);
	out = mv_mul(rotate, vec4(out, 1));
	return (out);
}
