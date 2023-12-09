/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:30:53 by sunko             #+#    #+#             */
/*   Updated: 2023/12/09 23:39:12 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

t_vec3	vec3(const double x, const double y, const double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_point3	point3(const double x, const double y, const double z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color3	color3(const double r, const double g, const double b)
{
	t_color3	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

void	set_vet(t_vec3 *vec, const double x, const double y, const double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

void	set_color(t_color3 *color, const double r, const double g, const double v)
{
	color->x = r;
	color->y = g;
	color->z = v;
}
