/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:54 by seunan            #+#    #+#             */
/*   Updated: 2023/12/12 14:46:08 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	check_range(double dst, double from, double to)
{
	if (!(from <= dst && dst <= to))
		ft_error("File Format Error");
}

void	check_rgb(t_color3 rgb)
{
	int	val;

	val = (int) rgb.x;
	if (rgb.x < 0.0 || rgb.x > 255.0 || val * 10 != rgb.x * 10)
		ft_error("File Format Error");
	val = (int) rgb.y;
	if (rgb.y < 0.0 || rgb.y > 255.0 || val * 10 != rgb.y * 10)
		ft_error("File Format Error");
	val = (int) rgb.z;
	if (rgb.z < 0.0 || rgb.z > 255.0 || val * 10 != rgb.z * 10)
		ft_error("File Format Error");
}

void	gen_ambient(t_vars *vars, char *line)
{
	vars->ambient.lighting_ratio = parse_double(&line);
	vars->ambient.rgb = parse_vec(&line, TRUE);
	++(vars->ambient.cnt);
}

void	gen_camera(t_vars *vars, char *line)
{
	vars->camera.view_point = parse_vec(&line, FALSE);
	vars->camera.direct_v = parse_vec(&line, FALSE);
	vars->camera.fov = parse_double(&line);
	while (*line == ' ')
		line++;
	if (*line != '\n')
		ft_error("File Format Error");
	++(vars->camera.cnt);
}

void	gen_light(t_vars *vars, char *line)
{
	vars->light.light_point = parse_vec(&line, FALSE);
	vars->light.brightness_ratio = parse_double(&line);
	vars->light.rgb = parse_vec(&line, TRUE);
	++(vars->light.cnt);
}
