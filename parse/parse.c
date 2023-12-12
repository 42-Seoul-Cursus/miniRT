/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:37:00 by seunan            #+#    #+#             */
/*   Updated: 2023/12/12 14:45:47 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"

static void	check_identifier(t_vars *vars, char *line);
static int	protected_open(char *path);

void	parse_rt(t_vars *vars, char *path)
{
	char	*line;
	int		fd;

	fd = protected_open(path);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		check_identifier(vars, line);
		free(line);
	}
}

static void	check_identifier(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "A ", 2) == 0)
		gen_ambient(vars, line + 1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		gen_camera(vars, line + 1);
	else if (ft_strncmp(line, "L ", 2) == 0)
		gen_light(vars, line + 1);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		gen_sphere(vars, line + 2);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		gen_plane(vars, line + 2);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		gen_cylinder(vars, line + 2);
	else if (*line == '\n' && *(line + 1) == '\0')
		return ;
	else
		ft_error("File Format Error");
}

double	parse_double(char **line)
{
	double	ans;
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
	ans = ft_strtod(tmp);
	free(tmp);
	*line += i;
	return (ans);
}

t_vec3	parse_vec(char **line, int is_endl)
{
	t_vec3	ans;

	ans.x = parse_double(line);
	while (**line == ' ')
		++line;
	if (**line != ',')
		ft_error("File Format Error");
	++(*line);
	ans.y = parse_double(line);
	while (**line == ' ')
		++(*line);
	if (**line != ',')
		ft_error("File Format Error");
	++(*line);
	ans.z = parse_double(line);
	while (is_endl && **line == ' ')
		++(*line);
	if (**line != '\n' && **line != ' ')
		ft_error("File Format Error");
	return (ans);
}

static int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}
