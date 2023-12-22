/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:11:27 by seunan            #+#    #+#             */
/*   Updated: 2023/12/17 18:21:23 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parse.h"

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
