#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

#define MAX_SAFE_INTEGER 9007199254740990

static void	make_double(char *s, double *integer, double *fractional, int *neg);
static void	make_fractional(char *s, double *fractional);
static void	error(void);

static size_t	is_size(long long n)
{
	size_t	size;

	if (n == 0)
		return (1);
	size = 0;
	while (n != 0)
	{
		n /= 10;
		++size;
	}
	return (size);
}

char	*ft_itoa(long long n)
{
	char		*num;
	int			minus;
	long long	ncpy;
	int			i;

	ncpy = n;
	minus = 0;
	if (ncpy < 0)
	{
		ncpy *= -1;
		++minus;
	}
	num = calloc(sizeof(char), (is_size(n) + minus + 1));
	if (!num)
		return (0);
	i = is_size(n) + minus;
	while (--i >= 0)
	{
		num[i] = ncpy % 10 + '0';
		ncpy /= 10;
	}
	if (minus == 1)
		num[0] = '-';
	return (num);
}

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
	ft_putendl_fd("Error\nFile Format Error", 2);
	exit(EXIT_FAILURE);
}

#include <stdio.h>
#include <unistd.h>
#include <float.h>

int	main(void)
{
	/* printf("%lf\n", ft_strtod("32123.123"));
	printf("%lf\n", ft_strtod("32123.123456789"));
	printf("%lf\n", ft_strtod("0.999999"));
	printf("%lf\n", ft_strtod("0.9999999"));
	printf("%lf\n", ft_strtod("-123456789.123456789"));
	printf("%lf\n", ft_strtod("0.0"));
	printf("%lf\n", ft_strtod("-0.0"));
	printf("%lf\n", ft_strtod("-9007199254740990"));
	printf("%lf\n", ft_strtod("9007199254740990"));

	// 오차
	printf("%lf\n", ft_strtod("-900719925474099.1"));
	printf("%lf\n", ft_strtod("-9007199254740990.123456"));

	// ERROR
	printf("%lf\n", ft_strtod(".12312"));
	printf("%lf\n", ft_strtod("0.")); */

	// printf("%ld\n", -9007199254740990);
	// printf("%lld\n", (long long)ft_strtod("-9007199254740990"));

	for (long long i = 0; i <= 9007199254740990; i++)
	{
		if (i != (long long)ft_strtod(ft_itoa(i)))
		{
			printf("i                     : %lld\n", i);
			printf("ft_strtod(ft_itoa(i)) : %lf\n", ft_strtod(ft_itoa(i)));
		}
		// sleep(1);
	}

	return (0);
}
