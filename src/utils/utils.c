/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:36:34 by seunan            #+#    #+#             */
/*   Updated: 2023/12/19 22:33:19 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* 인자가 하나고 확장자명이 '.rt'인 파일인지 확인*/
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

// 파싱할 때 하나만 들어와야하는 것들 cnt 초기화
void	init_vars(t_vars *vars)
{
	vars->ambient.cnt = 0;
	vars->camera.cnt = 0;
	vars->light = NULL;
	vars->objects = NULL;
}
