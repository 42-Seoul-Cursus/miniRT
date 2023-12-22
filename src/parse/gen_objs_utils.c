/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_objs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:57 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 16:16:30 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

void	gen_cylinder_cap(t_cylinder *cylinder, t_bool is_first)
{
	if (is_first)
	{
		cylinder->top.i_rgb = cylinder->i_rgb;
		cylinder->top.r_rgb = cylinder->r_rgb;
		cylinder->top.uvmap = cylinder->uvmap;
		cylinder->top.checker = cylinder->checker;
		cylinder->bottom.i_rgb = cylinder->i_rgb;
		cylinder->bottom.r_rgb = cylinder->r_rgb;
		cylinder->bottom.uvmap = cylinder->uvmap;
		cylinder->bottom.checker = cylinder->checker;
	}
	cylinder->top.normal_v = cylinder->normal_v;
	cylinder->top.point = v_plus(cylinder->center, \
		vt_mul(cylinder->normal_v, cylinder->height));
	cylinder->bottom.normal_v = vt_mul(cylinder->normal_v, -1);
	cylinder->bottom.point = cylinder->center;
}

void	gen_cone_cap(t_cone *cone, t_bool is_first)
{
	if (is_first)
	{
		cone->bottom.i_rgb = cone->i_rgb;
		cone->bottom.r_rgb = cone->r_rgb;
		cone->bottom.uvmap = cone->uvmap;
		cone->bottom.checker = cone->checker;
	}
	cone->bottom.normal_v = vt_mul(cone->normal_v, -1);
	cone->bottom.point = cone->center;
}
