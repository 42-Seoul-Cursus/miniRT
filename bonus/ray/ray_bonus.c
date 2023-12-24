/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:15:01 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 20:20:34 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
