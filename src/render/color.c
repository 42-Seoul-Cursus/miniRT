/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:48:22 by seunan            #+#    #+#             */
/*   Updated: 2023/12/22 14:03:03 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"

t_color3	get_color_int_to_real(t_color3 i_rgb)
{
	t_color3	out;

	out.x = i_rgb.x / 255;
	out.y = i_rgb.y / 255;
	out.z = i_rgb.z / 255;
	return (out);
}

t_color3	get_color_real_to_int(t_color3 r_rgb)
{
	t_color3	out;

	out.x = r_rgb.x * 255.999;
	out.y = r_rgb.y * 255.999;
	out.z = r_rgb.z * 255.999;
	return (out);
}

int	create_trgb(int t, t_color3 *color)
{
	return (t << 24 | (int)color->x << 16 | (int)color->y << 8 | (int)color->z);
}

void	my_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	extract_uv_color(t_mlx_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + y * data->line_length + x * data->bits_per_pixel / 8;
	return (*(unsigned int *)dst);
}
