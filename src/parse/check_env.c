/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:15:10 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 20:47:58 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

void	check_ambient(t_ambient *ambient)
{
	if (ambient->cnt != 1)
		ft_error("File Format Error");
	if (!check_range(ambient->lighting_ratio, 0, 1))
		ft_error("File Format Error");
	if (!check_vec(ambient->i_rgb, 0, 255, TRUE))
		ft_error("File Format Error");
}

void	check_camera(t_camera *camera)
{
	if (camera->cnt != 1)
		ft_error("File Format Error");
	if (!check_vec(camera->direct_v, -1, 1, FALSE))
		ft_error("File Format Error");
	if (!check_range(camera->fov, 0, 180))
		ft_error("File Format Error");
}

void	check_light(t_light *light)
{
	if (!check_range(light->brightness_ratio, 0, 1))
		ft_error("File Format Error");
	if (!check_vec(light->i_rgb, 0, 255, TRUE))
		ft_error("File Format Error");
}

void	check_checker_board(t_checker_map *checker)
{
	if (!check_vec(checker->rgb1, 0, 255, TRUE))
		ft_error("File Format Error");
	if (!check_vec(checker->rgb2, 0, 255, TRUE))
		ft_error("File Format Error");
	if (checker->width <= 0 || checker->height <= 0)
		ft_error("File Format Error");
}
