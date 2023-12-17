/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:11 by seunan            #+#    #+#             */
/*   Updated: 2023/12/17 14:50:29 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	make_int(const char *s, int *num, int *neg);

int	ft_atoi(const char *s)
{
	int			num;
	int			neg;

	num = 0;
	neg = 1;
	make_int(s, &num, &neg);
	return (neg * num);
}

static void	make_int(const char *s, int *num, int *neg)
{
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*neg *= -1;
		++s;
	}
	if (!ft_isdigit(*s))
		ft_error("File Format Error");
	while (ft_isdigit(*s))
	{
		if (*num > INT_MAX / 10 || (*num == INT_MAX / 10 && *s > '7'))
			ft_error("File Format Error");
		*num = *num * 10 + *s - '0';
		++s;
	}
	if (*s != '\0')
		ft_error("File Format Error");
}
