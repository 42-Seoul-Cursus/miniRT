/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:57 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 00:34:08 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "render.h"
#include "libft.h"
#include "utils.h"

void	gen_sphere(t_vars *vars, char *line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	sphere->uvmap = NULL;
	sphere->checker = NULL;
	sphere->center = parse_vec(&line);
	sphere->radius = parse_double(&line) / 2;
	sphere->i_rgb = parse_vec(&line);
	check_map(vars, sphere, line, SPHERE);
	check_sphere(sphere);
	sphere->r_rgb = get_color_int_to_real(sphere->i_rgb);
	ft_lstadd_back(&(vars->objects), ft_lstnew(sphere, SPHERE));
}

void	gen_plane(t_vars *vars, char *line)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	plane->uvmap = NULL;
	plane->checker = NULL;
	plane->point = parse_vec(&line);
	plane->normal_v = parse_vec(&line);
	plane->normal_v_basis = get_orthogonal_basis(plane->normal_v);
	plane->i_rgb = parse_vec(&line);
	check_map(vars, plane, line, PLANE);
	check_plane(plane);
	plane->r_rgb = get_color_int_to_real(plane->i_rgb);
	ft_lstadd_back(&(vars->objects), ft_lstnew(plane, PLANE));
}

void	gen_cylinder(t_vars *vars, char *line)
{
	t_cylinder		*cylinder;

	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	cylinder->uvmap = NULL;
	cylinder->center = parse_vec(&line);
	cylinder->normal_v = parse_vec(&line);
	cylinder->radius = parse_double(&line) / 2;
	cylinder->height = parse_double(&line);
	cylinder->i_rgb = parse_vec(&line);
	check_map(vars, cylinder, line, CYLINDER);
	check_cylinder(cylinder);
	cylinder->normal_v = v_unit(cylinder->normal_v);
	cylinder->r_rgb = get_color_int_to_real(cylinder->i_rgb);
	gen_cylinder_cap(cylinder);
	ft_lstadd_back(&(vars->objects), ft_lstnew(cylinder, CYLINDER));
}

void	gen_cylinder_cap(t_cylinder *cylinder)
{
	cylinder->top.normal_v = cylinder->normal_v;
	cylinder->top.i_rgb = cylinder->i_rgb;
	cylinder->top.r_rgb = cylinder->r_rgb;
	cylinder->top.point = v_plus(cylinder->center, \
		vt_mul(cylinder->normal_v, cylinder->height));
	cylinder->bottom.normal_v = vt_mul(cylinder->normal_v, -1);
	cylinder->bottom.i_rgb = cylinder->i_rgb;
	cylinder->bottom.r_rgb = cylinder->r_rgb;
	cylinder->bottom.point = cylinder->center;
}
