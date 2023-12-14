/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:15:10 by seunan            #+#    #+#             */
/*   Updated: 2023/12/14 14:15:00 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft/libft.h"

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

int	check_range(double dst, double from, double to)
{
	if (from <= dst && dst <= to)
		return (TRUE);
	return (FALSE);
}

int	check_vec(t_vec3 vec, double from, double to, enum e_bool is_int)
{
	int	integer;

	if (is_int)
	{
		integer = (int) vec.x;
		if (!check_range(vec.x, from, to) || integer * 10 != vec.x * 10)
			return (FALSE);
		integer = (int) vec.y;
		if (!check_range(vec.y, from, to) || integer * 10 != vec.y * 10)
			return (FALSE);
		integer = (int) vec.z;
		if (!check_range(vec.z, from, to) || integer * 10 != vec.z * 10)
			return (FALSE);
	}
	else
	{
		if (!check_range(vec.x, from, to))
			return (FALSE);
		if (!check_range(vec.y, from, to))
			return (FALSE);
		if (!check_range(vec.z, from, to))
			return (FALSE);
	}
	return (TRUE);
}
