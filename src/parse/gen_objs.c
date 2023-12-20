/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:57 by seunan            #+#    #+#             */
/*   Updated: 2023/12/20 15:00:00 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "render.h"
#include "libft.h"
#include "utils.h"

static void	gen_cylinder_cap(t_cylinder *cylinder);

void	gen_sphere(t_list **objects, char *line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	sphere->center = parse_vec(&line);
	sphere->diameter = parse_double(&line);
	sphere->i_rgb = parse_vec(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	check_sphere(sphere);
	sphere->r_rgb = get_color_int_to_real(sphere->i_rgb);
	sphere->radius = sphere->diameter / 2;
	ft_lstadd_back(objects, ft_lstnew(sphere, SPHERE));
}

void	gen_plane(t_list **objects, char *line)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	plane->point = parse_vec(&line);
	plane->normal_v = parse_vec(&line);
	plane->i_rgb = parse_vec(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	check_plane(plane);
	plane->r_rgb = get_color_int_to_real(plane->i_rgb);
	plane->normal_v_basis = get_orthogonal_basis(plane->normal_v);
	ft_lstadd_back(objects, ft_lstnew(plane, PLANE));
}

void	gen_cylinder(t_list **objects, char *line)
{
	t_cylinder		*cylinder;

	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	cylinder->center = parse_vec(&line);
	cylinder->normal_v = parse_vec(&line);
	cylinder->diameter = parse_double(&line);
	cylinder->height = parse_double(&line);
	cylinder->i_rgb = parse_vec(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	check_cylinder(cylinder);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->r_rgb = get_color_int_to_real(cylinder->i_rgb);
	gen_cylinder_cap(cylinder);
	ft_lstadd_back(objects, ft_lstnew(cylinder, CYLINDER));
}

void	gen_cylinder_cap(t_cylinder *cylinder)
{
	cylinder->top.normal_v = cylinder->normal_v;
	cylinder->top.i_rgb = cylinder->i_rgb;
	cylinder->top.r_rgb = cylinder->r_rgb;
	cylinder->top.point = v_plus(cylinder->center, \
		vt_mul(cylinder->normal_v, cylinder->height));
	cylinder->bottom.normal_v = cylinder->normal_v;
	cylinder->bottom.i_rgb = cylinder->i_rgb;
	cylinder->bottom.r_rgb = cylinder->r_rgb;
	cylinder->bottom.point = cylinder->center;
}
