/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:15:06 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 23:23:44 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "utils.h"

void	check_sphere(t_sphere *sphere)
{
	if (!check_vec(sphere->i_rgb, 0, 255, TRUE))
		ft_error("sp: Invalid RGB Value (0 ~ 255)");
	if (sphere->radius <= 0)
		ft_error("sp: Invalid Diameter Value");
}

void	check_plane(t_plane *plane)
{
	if (!check_vec(plane->normal_v, -1, 1, FALSE))
		ft_error("pl: Normal Vector Out of Range (-1, 1)");
	if (!check_vec(plane->i_rgb, 0, 255, TRUE))
		ft_error("pl: Invalid RGB Value (0 ~ 255)");
}

void	check_cylinder(t_cylinder *cylinder)
{
	if (!check_vec(cylinder->normal_v, -1, 1, FALSE))
		ft_error("cy: Normal Vector Out of Range (-1, 1)");
	if (!check_vec(cylinder->i_rgb, 0, 255, TRUE))
		ft_error("cy: Invalid RGB Value (0 ~ 255)");
	if (cylinder->radius <= 0)
		ft_error("cy: Invalid Diameter Value");
	if (cylinder->height <= 0)
		ft_error("cy: Invalid Height Value");
}

void	check_cone(t_cone *cone)
{
	if (!check_vec(cone->normal_v, -1, 1, FALSE))
		ft_error("cn: Normal Vector Out of Range (-1, 1)");
	if (!check_vec(cone->i_rgb, 0, 255, TRUE))
		ft_error("cn: Invalid RGB Value (0 ~ 255)");
	if (cone->radius <= 0)
		ft_error("cn: Invalid Diameter Value");
	if (cone->height <= 0)
		ft_error("cn: Invalid Height Value");
}
