/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 21:57:16 by sunko             #+#    #+#             */
/*   Updated: 2023/12/15 23:27:11 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int	hit_obj(t_list *object, t_ray *ray, t_hit_record *rec)
{
	int		is_hit;

	is_hit = 0;
	if (object->type == SPHERE)
		is_hit = hit_sphere((t_sphere *)object->content, ray, rec);
	else if (object->type == PLANE)
		is_hit = hit_plane((t_plane *)object->content, ray, rec);
	return (is_hit);
}

int	hit(t_list *objects, t_ray *ray, t_hit_record *rec)
{
	int				is_hit;
	t_hit_record	temp_rec;

	is_hit = 0;
	temp_rec = *rec;
	while (objects)
	{
		if (hit_obj(objects, ray, &temp_rec))
		{
			is_hit = 1;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		objects = objects->next;
	}
	return (is_hit);
}

int	in_shadow(t_list *object, t_ray ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 1e-6;
	rec.tmax = light_len;
	if (hit(object, &ray, &rec))
		return (1);
	return (0);
}

t_color3	ray_color(t_vars *vars)
{
	vars->rec.tmin = 1e-6;
	vars->rec.tmax = INFINITY;
	if (hit(vars->objects, &vars->ray, &vars->rec))
		return (execute_phong(vars));
	return (color3(0.9, 0.9, 0.9));
}
