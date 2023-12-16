/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/16 16:58:38 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	double	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	double	b = 2 * (ray->orig.x * ray->dir.x + ray->orig.z * ray->dir.z - cylinder->center.x * ray->dir.x - cylinder->center.z * ray->dir.z);
	double	c = ray->orig.x * ray->orig.x + cylinder->center.x * cylinder->center.x + \
				ray->orig.z * ray->orig.z + cylinder->center.z * cylinder->center.z \
				- 2 * (ray->orig.x * cylinder->center.x + ray->orig.z * cylinder->center.z) - cylinder->radius * cylinder->radius;
	double	oc = b * b - 4 * a * c;

	if (oc < -10e-4)
		return (0);
	double	t1 = (-b - sqrt(oc)) / (2 * a);
	double	t2 = (-b + sqrt(oc)) / (2 * a);
	double	t;
	if (t1 > t2)
		t = t2;
	else
		t = t1;
	double r = ray->orig.y + t * ray->dir.y;
	if (!(cylinder->center.y - cylinder->height <= r && r <= cylinder->center.y + cylinder->height))
		return (0);
	rec->t = t;
	rec->color = cylinder->r_rgb;
	rec->p = ray_at(ray, t);
	rec->normal = cylinder->normal_v;
	return (1);
}
