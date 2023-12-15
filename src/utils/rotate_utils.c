/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:09:26 by seunan            #+#    #+#             */
/*   Updated: 2023/12/15 16:09:53 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structures.h"
#include "utils.h"

t_4x4matrix	rotate_matrix(t_vec3 axis, float angle)
{
	t_4x4matrix	mat;
	float		s;
	float		c;
	float		t;

	axis = v_unit(axis);
	s = sin(angle);
	c = cos(angle);
	t = 1.0f - c;
	mat = unit_matrix();
	mat.r1.x = t * axis.x * axis.x + c;
	mat.r1.y = t * axis.x * axis.y - s * axis.z;
	mat.r1.z = t * axis.x * axis.z + s * axis.y;
	mat.r2.x = t * axis.x * axis.y + s * axis.z;
	mat.r2.y = t * axis.y * axis.y + c;
	mat.r2.z = t * axis.y * axis.z - s * axis.x;
	mat.r3.x = t * axis.x * axis.z - s * axis.y;
	mat.r3.y = t * axis.y * axis.z + s * axis.x;
	mat.r3.z = t * axis.z * axis.z + c;
	return (mat);
}

t_4x4matrix	create_view_matrix(t_camera camera, float angle_x, float angle_y)
{
	t_4x4matrix	rotation_matrix;
	t_4x4matrix	view_matrix;
	t_vec3		right;
	t_vec3		up;

	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	rotation_matrix = rotate_matrix(right, angle_y);
	rotation_matrix = mm_mul(rotation_matrix, rotate_matrix(up, angle_x));
	view_matrix = unit_matrix();
	view_matrix.r1.x = rotation_matrix.r1.x;
	view_matrix.r1.y = rotation_matrix.r2.x;
	view_matrix.r1.z = rotation_matrix.r3.x;
	view_matrix.r2.x = rotation_matrix.r1.y;
	view_matrix.r2.y = rotation_matrix.r2.y;
	view_matrix.r2.z = rotation_matrix.r3.y;
	view_matrix.r3.x = rotation_matrix.r1.z;
	view_matrix.r3.y = rotation_matrix.r2.z;
	view_matrix.r3.z = rotation_matrix.r3.z;
	view_matrix.r4.x = -v_dot(right, camera.view_point);
	view_matrix.r4.y = -v_dot(up, camera.view_point);
	view_matrix.r4.z = v_dot(camera.direct_v, camera.view_point);
	return (view_matrix);
}

t_4x4matrix	get_inverse_rotate_m(t_4x4matrix rotate)
{
	t_4x4matrix	inverse_rotate;

	inverse_rotate.r1.x = rotate.r1.x;
	inverse_rotate.r1.y = rotate.r2.x;
	inverse_rotate.r1.z = rotate.r3.x;
	inverse_rotate.r1.w = 0;
	inverse_rotate.r2.x = rotate.r1.y;
	inverse_rotate.r2.y = rotate.r2.y;
	inverse_rotate.r2.z = rotate.r3.y;
	inverse_rotate.r2.w = 0;
	inverse_rotate.r3.x = rotate.r1.z;
	inverse_rotate.r3.y = rotate.r2.z;
	inverse_rotate.r3.z = rotate.r3.z;
	inverse_rotate.r3.w = 0;
	inverse_rotate.r4.x = 0;
	inverse_rotate.r4.y = 0;
	inverse_rotate.r4.z = 0;
	inverse_rotate.r4.w = 1;
	return (inverse_rotate);
}
