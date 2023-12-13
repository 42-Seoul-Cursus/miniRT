/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:15:06 by seunan            #+#    #+#             */
/*   Updated: 2023/12/13 21:35:34 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	check_sphere(t_sphere *sphere)
{
	check_vec(sphere->i_rgb, 0, 255, TRUE);
}

void	check_plane(t_plane *plane)
{
	check_vec(plane->normal_v, -1, 1, FALSE);
	check_vec(plane->i_rgb, 0, 255, TRUE);
}

void	check_cylinder(t_cylinder *cylinder)
{
	check_vec(cylinder->normal_v, -1, 1, FALSE);
	check_vec(cylinder->i_rgb, 0, 255, TRUE);
}
