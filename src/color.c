/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:48:22 by seunan            #+#    #+#             */
/*   Updated: 2023/12/13 15:55:32 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "minirt.h"

t_color3	get_color_int_to_real(t_color3 rgb)
{
	t_color3	out;

	out.x = rgb.x / 255;
	out.y = rgb.y / 255;
	out.z = rgb.z / 255;
	return (out);
}

t_color3	get_color_real_to_int(t_color3 rgb)
{
	t_color3	out;

	out.x = rgb.x * 255.999;
	out.y = rgb.y * 255.999;
	out.z = rgb.z * 255.999;
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
