/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:09:26 by seunan            #+#    #+#             */
/*   Updated: 2023/12/16 15:58:25 by sunko            ###   ########.fr       */
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
