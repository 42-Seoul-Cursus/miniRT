/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:57 by seunan            #+#    #+#             */
/*   Updated: 2023/12/13 18:13:21 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft/libft.h"

void	gen_sphere(t_list **objects, char *line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	sphere->center = parse_vec(&line, FALSE);
	sphere->diameter = parse_double(&line);
	sphere->radius = sphere->diameter / 2;
	sphere->rgb = parse_vec(&line, TRUE);
	check_sphere(sphere);
	ft_lstadd_back(objects, ft_lstnew(sphere, SPHERE));
}

void	gen_plane(t_list **objects, char *line)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	plane->point = parse_vec(&line, FALSE);
	plane->normal_v = parse_vec(&line, FALSE);
	plane->rgb = parse_vec(&line, TRUE);
	check_plane(plane);
	ft_lstadd_back(objects, ft_lstnew(plane, PLANE));
}

void	gen_cylinder(t_list **objects, char *line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	cylinder->center = parse_vec(&line, FALSE);
	cylinder->normal_v = parse_vec(&line, FALSE);
	cylinder->diameter = parse_double(&line);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = parse_double(&line);
	cylinder->rgb = parse_vec(&line, TRUE);
	check_cylinder(cylinder);
	ft_lstadd_back(objects, ft_lstnew(cylinder, CYLINDER));
}
