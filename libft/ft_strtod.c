#include <stdlib.h>
#include "libft.h"

#define MAX_SAFE_INTEGER 9007199254740990

static void	make_double(char *s, double *integer, double *fractional, int *neg);
static void	make_fractional(char *s, double *fractional);
static void	error(void);

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
		error();
	while (ft_isdigit(*s))
	{
		if (*integer >= MAX_SAFE_INTEGER / 10 && *s > '0')
			error();
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
			error();
		while (len > 6)
		{
			*fractional = (int) *fractional / 10;
			--len;
		}
		while (len > 0)
		{
			*fractional /= 10;
			--len;
		}
	}
}

static void	error(void)
{
	ft_putendl_fd("Error\nFile Format Error\n", 2);
	exit(1);
}

#include <stdio.h>
#include <float.h>

int	main(void)
{
	printf("%lf\n", ft_strtod("32123.123"));
	printf("%lf\n", ft_strtod("32123.123456789"));
	printf("%lf\n", ft_strtod("0.999999"));
	printf("%lf\n", ft_strtod("0.9999999"));
	printf("%lf\n", ft_strtod("-123456789.123456789"));
	printf("%lf\n", ft_strtod("0.0"));
	printf("%lf\n", ft_strtod("-0.0"));
	// TODO: 오차 생김
	printf("%lf\n", ft_strtod("-900719925474099.1"));
	printf("%lf\n", ft_strtod("-9007199254740990"));
	printf("%lf\n", ft_strtod("-9007199254740990.123456"));
	printf("%lf\n", ft_strtod(".12312"));
	printf("%lf\n", ft_strtod("0."));
	return (0);
}
