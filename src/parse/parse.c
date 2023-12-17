/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:37:00 by seunan            #+#    #+#             */
/*   Updated: 2023/12/17 14:40:12 by seunan           ###   ########.fr       */
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
	if (vars->camera.cnt == 0 || vars->ambient.cnt == 0 || vars->light == NULL)
		ft_error("File Format Error");
}

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
	return (out);
}

t_vec3	parse_vec(char **line, enum e_bool is_endl)
{
	t_vec3	out;

	out.x = parse_double(line);
	while (**line == ' ')
		++line;
	if (**line != ',')
		ft_error("File Format Error");
	++(*line);
	out.y = parse_double(line);
	while (**line == ' ')
		++(*line);
	if (**line != ',')
		ft_error("File Format Error");
	++(*line);
	out.z = parse_double(line);
	while (is_endl && **line == ' ')
		++(*line);
	if (**line != '\n' && **line != ' ')
		ft_error("File Format Error");
	return (out);
}

void	check_uvmap(t_uvmap *uvmap)
{
	if (uvmap->cnt != 1)
		ft_error("File Format Error");
	if (!check_vec(uvmap->rgb1, 0, 255, TRUE))
		ft_error("File Format Error");
	if (!check_vec(uvmap->rgb2, 0, 255, TRUE))
		ft_error("File Format Error");
	if (uvmap->width <= 0 || uvmap->height <= 0)
		ft_error("File Format Error");
}

void	gen_uvmap(t_uvmap *uvmap, char *line)
{
	uvmap->rgb1 = parse_vec(&line, FALSE);
	uvmap->rgb2 = parse_vec(&line, FALSE);
	uvmap->width = parse_int(&line);
	while (*line == ' ')
		line++;
	uvmap->height = parse_int(&line);
	while (*line == ' ')
		line++;
	if (*line != '\n' || *line != '\0')
		ft_error("File Format Error");
	++(uvmap->cnt);
	check_uvmap(uvmap);
}

static void	check_identifier(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "A ", 2) == 0)
		gen_ambient(&(vars->ambient), line + 1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		gen_camera(&(vars->camera), line + 1);
	else if (ft_strncmp(line, "L ", 2) == 0)
		gen_light(&(vars->light), line + 1);
	else if (ft_strncmp(line, "UV ", 3) == 0)
		gen_uvmap(&(vars->uvmap), line + 2);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		gen_sphere(&(vars->objects), line + 2);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		gen_plane(&(vars->objects), line + 2);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		gen_cylinder(&(vars->objects), line + 2);
	else if (*line == '\n' && *(line + 1) == '\0')
		return ;
	else
		ft_error("File Format Error");
}

static int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}
