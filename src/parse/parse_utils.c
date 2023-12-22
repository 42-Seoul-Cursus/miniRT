/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:11:27 by seunan            #+#    #+#             */
/*   Updated: 2023/12/17 18:21:23 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parse.h"

int	parse_int(char **line)
{
	int		out;
	char	*tmp;
	int		i;

	while (**line == ' ')
		++(*line);
	i = 0;
	if (ft_issign((*line)[i]))
		++i;
	while (ft_isdigit((*line)[i]))
		++i;
	tmp = ft_substr(*line, 0, i);
	out = ft_atoi(tmp);
	free(tmp);
	*line += i;
	while (**line == ' ')
		++(*line);
	return (out);
}

char	*parse_path(char **line)
{
	char	*out;
	int		i;

	while (**line == ' ')
		++(*line);
	i = 0;
	while ((*line)[i] != ' ' && (*line)[i] != '\n' && (*line)[i] != '\0')
		++i;
	out = ft_substr(*line, 0, i);
	*line += i;
	while (**line == ' ')
		++(*line);
	return (out);
}

double	parse_double(char **line)
{
	double	out;
	char	*tmp;
	int		i;

	while (**line == ' ')
		++(*line);
	i = 0;
	if (ft_issign((*line)[i]))
		++i;
	while (ft_isdigit((*line)[i]) || (*line)[i] == '.')
		++i;
	tmp = ft_substr(*line, 0, i);
	out = ft_strtod(tmp);
	free(tmp);
	*line += i;
	while (**line == ' ')
		++(*line);
	return (out);
}

t_vec3	parse_vec(char **line)
{
	t_vec3	out;

	out.x = parse_double(line);
	if (**line != ',')
		ft_error("File Format Error");
	++(*line);
	out.y = parse_double(line);
	if (**line != ',')
		ft_error("File Format Error");
	++(*line);
	out.z = parse_double(line);
	return (out);
}
