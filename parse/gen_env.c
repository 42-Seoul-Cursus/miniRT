/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:54 by seunan            #+#    #+#             */
/*   Updated: 2023/12/12 16:27:41 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "vector.h"

void	gen_ambient(t_vars *vars, char *line)
{
	vars->ambient.lighting_ratio = parse_double(&line);
	vars->ambient.rgb = parse_vec(&line, TRUE);
	++(vars->ambient.cnt);
	check_ambient(vars->ambient);
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
	check_camera(vars->camera);
	vars->camera.viewport_width = 2;
	vars->camera.viewport_height = 2 * IMG_RATIO;
	vars->camera.viewport_u = vec3(vars->camera.viewport_width, 0, 0);
	vars->camera.viewport_v = vec3(0, -vars->camera.viewport_height, 0);
	vars->camera.pixel_delta_u = vt_divide(vars->camera.viewport_u, WIDTH);
	vars->camera.pixel_delta_v = vt_divide(vars->camera.viewport_v, HEIGHT);
}

void	gen_light(t_vars *vars, char *line)
{
	vars->light.light_point = parse_vec(&line, FALSE);
	vars->light.brightness_ratio = parse_double(&line);
	vars->light.rgb = parse_vec(&line, TRUE);
	++(vars->light.cnt);
	check_light(vars->light);
}
