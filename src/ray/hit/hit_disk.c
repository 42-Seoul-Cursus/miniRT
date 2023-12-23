/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_disk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:02:36 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 20:25:46 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"

t_bool	hit_disk(t_plane *disk, double radius, t_ray *ray, t_hit_record *rec)
{
	t_point3		p;
	double			radius2;

	radius2 = radius * radius;
	if (hit_plane(disk, ray, rec))
	{
		p = v_minus(rec->p, disk->point);
		if (v_dot(p, p) <= radius2)
			return (TRUE);
	}
	return (FALSE);
}
