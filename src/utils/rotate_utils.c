/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:09:26 by seunan            #+#    #+#             */
/*   Updated: 2023/12/16 13:45:37 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structures.h"
#include "utils.h"

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
