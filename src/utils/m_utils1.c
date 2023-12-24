/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:42:50 by sunko             #+#    #+#             */
/*   Updated: 2023/12/24 14:58:33 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "libft.h"

t_4x4matrix	_4x4matrix(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4)
{
	t_4x4matrix	m;

	ft_bzero(&m, sizeof(t_4x4matrix));
	m.r1.x = r1.x;
	m.r1.y = r1.y;
	m.r1.z = r1.z;
	m.r1.w = r1.w;
	m.r2.x = r2.x;
	m.r2.y = r2.y;
	m.r2.z = r2.z;
	m.r2.w = r2.w;
	m.r3.x = r3.x;
	m.r3.y = r3.y;
	m.r3.z = r3.z;
	m.r3.w = r3.w;
	m.r4.x = r4.x;
	m.r4.y = r4.y;
	m.r4.z = r4.z;
	m.r4.w = r4.w;
	return (m);
}

t_vec3	mv_mul(t_4x4matrix m, t_vec4 v)
{
	t_vec3	rst;

	ft_bzero(&rst, sizeof(t_vec3));
	rst.x += m.r1.x * v.x;
	rst.x += m.r1.y * v.y;
	rst.x += m.r1.z * v.z;
	rst.x += m.r1.w * v.w;
	rst.y += m.r2.x * v.x;
	rst.y += m.r2.y * v.y;
	rst.y += m.r2.z * v.z;
	rst.y += m.r2.w * v.w;
	rst.z += m.r3.x * v.x;
	rst.z += m.r3.y * v.y;
	rst.z += m.r3.z * v.z;
	rst.z += m.r3.w * v.w;
	return (rst);
}

t_4x4matrix	get_rotate_matrix(t_camera *camera)
{
	t_4x4matrix	m;
	t_vec3		view_x;
	t_vec3		view_y;
	t_vec3		view_z;

	view_z = vt_mul(camera->direct_v, -1);
	if (camera->direct_v.y >= 1.0 - 10e-4 || camera->direct_v.y <= -1.0 + 10e-4)
		view_x = vec3(-1.0, 0.0, 0.0);
	else
		view_x = vt_mul(v_unit(v_cross(view_z, vec3(0.0, 1.0, 0.0))), -1);
	view_y = v_cross(view_z, view_x);
	m = _4x4matrix(vec4(view_x, 0.0), vec4(view_y, 0.0),
			vec4(view_z, 0.0), vec4(vec3(0.0, 0.0, 0.0), 1));
	return (m);
}

t_4x4matrix	get_inverse_matrix(t_4x4matrix rotate)
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

t_4x4matrix	get_orthogonal_basis(t_vec3	v1)
{
	t_vec3		u;
	t_vec3		v;
	t_4x4matrix	orthogonal_basis;

	u = v_cross(v1, vec3(1, 0, 0));
	if (v_length(u) == 0)
		u = v_cross(v1, vec3(0, 0, 1));
	u = v_unit(u);
	v = v_unit(v_cross(v1, u));
	orthogonal_basis = _4x4matrix(vec4(u, 0), vec4(v, 0), \
	vec4(v1, 0), vec4(vec3(0, 0, 0), 1));
	return (orthogonal_basis);
}
