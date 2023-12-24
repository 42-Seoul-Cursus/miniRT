/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:54 by seunan            #+#    #+#             */
/*   Updated: 2023/12/24 14:40:14 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse.h"
#include "utils.h"
#include "render.h"
#include "libft.h"

static int	ft_lstsize(t_list *lst);

void	gen_ambient(t_ambient *ambient, char *line)
{
	ambient->lighting_ratio = parse_double(&line);
	ambient->i_rgb = parse_vec(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	ambient->r_rgb = \
		vt_mul(get_color_int_to_real(ambient->i_rgb), ambient->lighting_ratio);
	++(ambient->cnt);
	check_ambient(ambient);
}

void	gen_camera(t_camera *camera, char *line)
{
	camera->view_point = parse_vec(&line);
	camera->direct_v = parse_vec(&line);
	camera->fov = parse_double(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	++(camera->cnt);
	check_camera(camera);
	camera->direct_v = v_unit(camera->direct_v);
	camera->viewport_width = 2;
	camera->viewport_height = 2 / IMG_RATIO;
	camera->viewport_u = vec3(camera->viewport_width, 0, 0);
	camera->viewport_v = vec3(0, -camera->viewport_height, 0);
	camera->pixel_delta_u = vt_divide(camera->viewport_u, WIDTH);
	camera->pixel_delta_v = vt_divide(camera->viewport_v, HEIGHT);
	camera->up_v = vec3(0, 1, 0);
}

void	gen_light(t_list **light, char *line)
{
	t_light	*new;

	new = (t_light *)ft_calloc(1, sizeof(t_light));
	new->light_point = parse_vec(&line);
	new->brightness_ratio = parse_double(&line);
	new->i_rgb = parse_vec(&line);
	if (*line != '\n' && *line != '\0')
		ft_error("File Format Error");
	check_light(new);
	new->r_rgb = \
		vt_mul(get_color_int_to_real(new->i_rgb), new->brightness_ratio);
	ft_lstadd_back(light, ft_lstnew(new, LIGHT));
	if (ft_lstsize(*light) > 1)
		ft_error("L: Must be Singular");
}

static int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		++size;
	}
	return (size);
}
