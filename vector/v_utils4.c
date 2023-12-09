/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:43:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/09 23:51:01 by sunko            ###   ########.fr       */
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

	len = get_vec_length(vec);
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
