/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:34 by seunan            #+#    #+#             */
/*   Updated: 2023/12/23 20:14:58 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	is_valid_arg(int ac, char *av[])
{
	int	i;
	int	slash;

	if (ac != 2)
		ft_error("Invalid number of arguments");
	i = 0;
	slash = 0;
	while (av[1][i] != '\0')
	{
		if (av[1][i] == '/')
			slash = i + 1;
		++i;
	}
	if (i - slash < 4 || av[1][i - 1] != 't'
		|| av[1][i - 2] != 'r' || av[1][i - 3] != '.')
		ft_error("The file must end with a \'.rt\'");
}

void	init_vars(t_vars *vars)
{
	vars->ambient.cnt = 0;
	vars->camera.cnt = 0;
	vars->light = NULL;
	vars->objects = NULL;
}

void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
