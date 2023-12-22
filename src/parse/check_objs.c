/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:15:06 by seunan            #+#    #+#             */
/*   Updated: 2023/12/15 16:36:51 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"
#include "utils.h"

void	check_sphere(t_sphere *sphere)
{
	check_vec(sphere->i_rgb, 0, 255, TRUE);
}

void	check_plane(t_plane *plane)
{
	check_vec(plane->normal_v, -1, 1, FALSE);
	plane->normal_v = v_unit(plane->normal_v);
	check_vec(plane->i_rgb, 0, 255, TRUE);
}

void	check_cylinder(t_cylinder *cylinder)
{
	check_vec(cylinder->normal_v, -1, 1, FALSE);
	check_vec(cylinder->i_rgb, 0, 255, TRUE);
}

void	check_cone(t_cone *cone)
{
	check_vec(cone->normal_v, -1, 1, FALSE);
	check_vec(cone->i_rgb, 0, 255, TRUE);
}
