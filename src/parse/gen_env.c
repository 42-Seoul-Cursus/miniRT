/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:54 by seunan            #+#    #+#             */
/*   Updated: 2023/12/13 17:10:42 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "vector.h"

void	gen_ambient(t_ambient *ambient, char *line)
{
	ambient->lighting_ratio = parse_double(&line);
	ambient->rgb = parse_vec(&line, TRUE);
	++(ambient->cnt);
	check_ambient(ambient);
}

void	gen_camera(t_camera *camera, char *line)
{
	camera->view_point = parse_vec(&line, FALSE);
	camera->direct_v = parse_vec(&line, FALSE);
	camera->fov = parse_double(&line);
	while (*line == ' ')
		line++;
	if (*line != '\n')
		ft_error("File Format Error");
	++(camera->cnt);
	check_camera(camera);
	camera->viewport_width = 2;
	camera->viewport_height = 2 / IMG_RATIO;
	camera->viewport_u = vec3(camera->viewport_width, 0, 0);
	camera->viewport_v = vec3(0, -camera->viewport_height, 0);
	camera->pixel_delta_u = vt_divide(camera->viewport_u, WIDTH);
	camera->pixel_delta_v = vt_divide(camera->viewport_v, HEIGHT);
}

void	gen_light(t_list **light, char *line)
{
	t_light	*new;

	new = (t_light *)ft_calloc(1, sizeof(t_light));
	new->light_point = parse_vec(&line, FALSE);
	new->brightness_ratio = parse_double(&line);
	new->rgb = parse_vec(&line, TRUE);
	check_light(new);
	ft_lstadd_back(light, ft_lstnew(new, LIGHT));
}
