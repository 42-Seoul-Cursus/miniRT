/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/23 20:21:05 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "utils.h"
#include "ray.h"

/* sphere, plane, cylinder 판별식에 ray를 쏴서 맞으면 is_hit = 1 */
t_bool	hit_obj(t_list *object, t_ray *ray, t_hit_record *rec)
{
	t_bool	is_hit;

	is_hit = FALSE;
	if (object->type == SPHERE)
		is_hit = hit_sphere((t_sphere *)object->content, ray, rec);
	else if (object->type == PLANE)
		is_hit = hit_plane((t_plane *)object->content, ray, rec);
	else if (object->type == CYLINDER)
		is_hit = hit_cylinder((t_cylinder *)object->content, ray, rec);
	else if (object->type == CONE)
		is_hit = hit_cone((t_cone *)object->content, ray, rec);
	return (is_hit);
}

/*
1. camera에서 ray를 쏠 때(물체를 그리기 위함)
2. in_shadow에서 object가 맞은 점에서 광원으로 ray를 쏠 때(그림자를 판단하기 위함)
temp_rec: 오브젝트에 hit 했을 때 rec에 갱신하기 위함
*/
t_bool	hit(t_vars *vars, t_ray *ray, t_hit_record *rec)
{
	t_bool			is_hit;
	t_list			*obj;
	t_hit_record	temp_rec;

	is_hit = FALSE;
	temp_rec = *rec;
	obj = vars->objects;
	while (obj)
	{
		if (hit_obj(obj, ray, &temp_rec))
		{
			is_hit = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		obj = obj->next;
	}
	return (is_hit);
}

t_bool	in_shadow(t_vars *vars, t_ray r, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 1e-6;
	rec.tmax = light_len;
	if (hit(vars, &r, &rec))
		return (TRUE);
	return (FALSE);
}

t_color3	ray_color(t_vars *vars)
{
	vars->rec.tmin = 1e-6;
	vars->rec.tmax = INFINITY;
	if (hit(vars, &vars->ray, &vars->rec))
		return (execute_phong(vars));
	return (color3(0.9, 0.9, 0.9));
}
