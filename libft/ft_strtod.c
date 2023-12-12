<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:14:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 00:15:05 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
=======
>>>>>>> main
#include <float.h>
#include "libft.h"

static void	make_double(char *s, double *integer, double *fractional, int *neg);
static void	make_fractional(char *s, double *fractional);

double	ft_strtod(char *s)
{
	double	integer;
	double	fractional;
	int		neg;

	integer = 0;
	fractional = 0;
	neg = 0;
	make_double(s, &integer, &fractional, &neg);
	if (neg)
		return (-integer - fractional);
	else
		return (integer + fractional);
}

static void	make_double(char *s, double *integer, double *fractional, int *neg)
{
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			*neg = 1;
		s++;
	}
	if (!ft_isdigit(*s))
		ft_error("File Format Error");
	while (ft_isdigit(*s))
	{
		if (*integer >= DBL_MAX / 10)
			ft_error("File Format Error");
		*integer = *integer * 10 + *s - '0';
		++s;
	}
	make_fractional(s, fractional);
}

static void	make_fractional(char *s, double *fractional)
{
	double	len;

	len = 0;
	if (*s == '.')
	{
		++s;
		while (ft_isdigit(*s))
		{
			*fractional = *fractional * 10 + *s - '0';
			++len;
			++s;
		}
		if (len == 0)
			ft_error("File Format Error");
		while (len > 0)
		{
			*fractional /= 10;
			--len;
		}
	}
	if (*s != '\0')
		ft_error("File Format Error");
}
