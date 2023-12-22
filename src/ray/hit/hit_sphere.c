/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:30:55 by sunko             #+#    #+#             */
/*   Updated: 2023/12/22 16:37:57 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include "ray.h"
#include <math.h>
#include <stdlib.h>
#include "mlx.h"

/* P - C: 법선 벡터
정규화된 법선 벡터: (P - C) / r */
static t_vec3	get_sphere_normal_v(t_sphere *sphere, t_hit_record *rec)
{
	t_vec3	normal_v;

	normal_v = v_unit(v_minus(rec->p, sphere->center));
	return (normal_v);
}

static int	update_nearest_hit_point(double a, \
	double b, double c, t_hit_record *rec)
{
	double	root;
	double	sqrtd;
	double	discriminant;

	discriminant = b * b - a * c;
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	rec->t = root;
	return (1);
}

<<<<<<< HEAD
static t_color3	get_check_color(t_sphere *sphere, \
	t_hit_record *rec, t_vars *vars)
=======
static t_color3	get_uvmap_color(t_sphere *sphere, t_hit_record *rec)
>>>>>>> main
{
	t_vec3	d;
	double	theta;
	double	phi;
	double	u;
	double	v;

	d = v_unit(v_minus(rec->p, sphere->center));
	theta = atan2(d.x, d.z);
	phi = acos(d.y / sphere->radius);
	u = 1 - (theta / (2 * M_PI) + 0.5);
	v = 1 - phi / M_PI;
	if (((int)(floor(u * sphere->checker->width)) \
		+ (int)(floor(v * sphere->checker->height))) % 2 == 0)
		return (get_color_int_to_real(sphere->checker->rgb1));
	else
		return (get_color_int_to_real(sphere->checker->rgb2));
}

<<<<<<< HEAD
#include <stdio.h>
static void	set_uv_color(t_sphere *sphere, t_hit_record *rec, t_vars *vars)
{
	double		u;
	double		v;
	unsigned	u_color;
	t_color3	v_color;
	// tmp variable
	t_mlx_data	texture = vars->texture;
	t_mlx_data	normal = vars->normal;

	// unused tmp
	(void)sphere;
	u = 1 - (atan2(rec->normal.x, rec->normal.z) / (2 * M_PI) + 0.5);
	v = 1 - acos(rec->normal.y / sphere->radius) / M_PI;
	/* texture */
	u_color = extract_uv_color(&texture, floor(u * vars->t_width), floor(v * vars->t_height));
	v_color = color3((u_color >> 16) & 0xFF, (u_color >> 8) & 0xFF, u_color & 0xFF);
	rec->color = get_color_int_to_real(v_color);
	/* normal */
	u_color = extract_uv_color(&normal, floor(u * vars->n_width), floor(v * vars->n_height));
	v_color = color3((u_color >> 16) & 0xFF, (u_color >> 8) & 0xFF, u_color & 0xFF);
	v_color = get_color_int_to_real(v_color);
	t_vec3	tmp = rec->normal;
	rec->normal = v_unit(v_minus(vt_mul(v_color, 2.0), vec3(1, 1, 1)));
	t_4x4matrix basis = get_orthogonal_basis(rec->normal);
	rec->normal = mv_mul(basis, vec4(tmp, 1));
	return ;
}

#include <stdio.h>
int	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec, t_vars *vars)
=======
int	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
>>>>>>> main
{
	double	a;
	double	b;
	double	c;

	a = v_length2(ray->dir);
	b = v_dot(v_minus(ray->orig, sphere->center), ray->dir);
	c = v_length2(\
	v_minus(ray->orig, sphere->center)) - sphere->radius * sphere->radius;
	if (b * b - a * c < 0 || update_nearest_hit_point(a, b, c, rec) == 0)
		return (0);
	rec->p = ray_at(ray, rec->t);
	rec->normal = get_sphere_normal_v(sphere, rec);
<<<<<<< HEAD
	if (v_dot(ray->dir, rec->normal) > 0)
		rec->normal = vt_mul(rec->normal, -1);
	if (vars->uvmap.cnt != 0)
		rec->color = sphere->r_rgb;
	else
	{
		if (1)
			set_uv_color(sphere, rec, vars);
		else
			rec->color = get_check_color(sphere, rec, vars);
	}
=======
	if (sphere->checker == NULL)
		rec->color = sphere->r_rgb;
	else
		rec->color = get_uvmap_color(sphere, rec);
	rec->front_face = v_dot(ray->dir, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vt_mul(rec->normal, -1);
>>>>>>> main
	return (1);
}
