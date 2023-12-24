/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:39:43 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 20:15:08 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"

double	v_length2(const t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	v_length(const t_vec3 vec)
{
	return (sqrt(v_length2(vec)));
}

t_vec3	v_plus(t_vec3 vec, const t_vec3 vec2)
{
	vec.x += vec2.x;
	vec.y += vec2.y;
	vec.z += vec2.z;
	return (vec);
}

t_vec3	vp_plus(t_vec3 vec, const double x, const double y, const double z)
{
	vec.x += x;
	vec.y += y;
	vec.z += z;
	return (vec);
}

t_vec3	v_minus(t_vec3 vec, const t_vec3 vec2)
{
	vec.x -= vec2.x;
	vec.y -= vec2.y;
	vec.z -= vec2.z;
	return (vec);
}
