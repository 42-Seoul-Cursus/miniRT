/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_cap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:02:36 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 01:05:43 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "ray.h"

int	hit_cylinder_cap(t_cylinder *cylinder, t_ray *ray, \
	t_hit_record *rec, t_vars *vars)
{
	t_plane		cap;
	t_point3	p;
	double		radius;

	radius = cylinder->radius;
	cap = cylinder->top;
	if (hit_plane(&cap, ray, rec, vars))
	{
		p = v_minus(rec->p, cap.point);
		if (v_dot(p, p) < radius * radius)
			return (1);
	}
	cap = cylinder->bottom;
	if (hit_plane(&cap, ray, rec, vars))
	{
		p = v_minus(rec->p, cap.point);
		if (v_dot(p, p) < radius * radius)
			return (1);
	}
	return (0);
}
