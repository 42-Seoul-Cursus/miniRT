/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:15:01 by sunko             #+#    #+#             */
/*   Updated: 2023/12/14 23:11:39 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = v_unit(dir);
	return (ray);
}

t_point3	ray_at(t_ray *ray, const double t)
{
	t_point3	at;

	at = v_plus(ray->orig, vt_mul(ray->dir, t));
	return (at);
}
