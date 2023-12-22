/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 22:16:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

static t_bool	hit_cone_body(t_cone *cone, t_ray *r, t_hit_record *rec);

t_bool	hit_cone(t_cone *cone, t_ray *ray, t_hit_record *rec)
{
	t_bool				is_hit;
	t_hit_record	temp_rec;

	is_hit = FALSE;
	temp_rec = *rec;
	if (hit_disk(&(cone->bottom), cone->radius, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_cone_body(cone, ray, &temp_rec))
	{
		is_hit = TRUE;
		temp_rec.tmax = temp_rec.t;
		*rec = temp_rec;
	}
	return (is_hit);
}

static t_bool	hit_cone_body(t_cone *cone, t_ray *r, t_hit_record *rec)
{
	(void) cone;
	(void) r;
	(void) rec;
	return (FALSE);
}
