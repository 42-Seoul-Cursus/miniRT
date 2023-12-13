/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:11 by seunan            #+#    #+#             */
/*   Updated: 2023/12/11 18:28:01 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdlib.h"

int	ft_atoi(const char *str)
{
	long long	num;
	int			min;
	int			i;

	num = 0;
	min = 1;
	i = 0;
	while (str[i] == ' ')
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			min *= -1;
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		if (num > 214748364 || (num == 214748364 && str[i] > '7'))
			ft_error("File Format Error");
		num = num * 10 + str[i] - '0';
		++i;
	}
	return (min * num);
}
