/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:42:50 by sunko             #+#    #+#             */
/*   Updated: 2023/12/14 20:30:58 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
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
