/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:43:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 22:51:08 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "libft.h"

t_vec3	v_cross(t_vec3 vec, t_vec3 vec2)
{
	t_vec3	rst;

	rst.x = vec.y * vec2.z - vec.z * vec2.y;
	rst.y = vec.z * vec2.x - vec.x * vec2.z;
	rst.z = vec.x * vec2.y - vec.y * vec2.x;
	return (rst);
}

t_vec3	v_unit(t_vec3 vec)
{
	double	len;

	len = v_length(vec);
	if (len == 0)
		ft_error("Not divisible by 0");
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vec4	vec4(t_vec3 v, const double w)
{
	t_vec4	v4;

	v4.x = v.x;
	v4.y = v.y;
	v4.z = v.z;
	v4.w = w;
	return (v4);
}

t_vec3	v_min(t_vec3 v1, t_vec3 v2)
{
	t_vec3	res;

	if (v1.x < v2.x)
		res.x = v1.x;
	else
		res.x = v2.x;
	if (v1.y < v2.y)
		res.y = v1.y;
	else
		res.y = v2.y;
	if (v1.z < v2.z)
		res.z = v1.z;
	else
		res.z = v2.z;
	return (res);
}

t_vec3	rotate_vec3(t_4x4matrix rotate, t_vec3 vector)
{
	t_vec3	result;

	result.x = rotate.r1.x * vector.x + \
	rotate.r1.y * vector.y + rotate.r1.z * vector.z;
	result.y = rotate.r2.x * vector.x + \
	rotate.r2.y * vector.y + rotate.r2.z * vector.z;
	result.z = rotate.r3.x * vector.x + \
	rotate.r3.y * vector.y + rotate.r3.z * vector.z;
	return (result);
}
