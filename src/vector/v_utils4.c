/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:43:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 17:04:56 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include <stdlib.h>

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
	{
		ft_putstr_fd("Error\n0 is not divisible", 2);
		exit(EXIT_FAILURE);
	}
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
