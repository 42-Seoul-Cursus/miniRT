#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include "../minirt.h"

#include <stdio.h>
static void	check_identifier(t_vars *vars, char *buf);
static void	make_ambient(t_vars *vars, char *line);
static void	make_camera(t_vars *vars, char *line);
static void	make_light(t_vars *vars, char *line);
static void	make_sphere(t_vars *vars, char *line);
static void	make_plane(t_vars *vars, char *line);
static void	make_cylinder(t_vars *vars, char *line);
static int	protected_open(char *path);
void static	parse_test(t_vars *vars);

void	init_vars(t_vars *vars)
{
	vars->ambient.b_start = 0;
	vars->camera.b_start = 0;
	vars->light.b_start = 0;
}

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
	parse_test(vars);
}

static void	check_identifier(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "A", 1) == 0 && *(line + 1) == ' ')
		make_ambient(vars, line + 1);
	else if (ft_strncmp(line, "C", 1) == 0 && *(line + 1) == ' ')
		make_camera(vars, line + 1);
	else if (ft_strncmp(line, "L", 1) == 0 && *(line + 1) == ' ')
		make_light(vars, line + 1);
	else if (ft_strncmp(line, "sp", 2) == 0 && *(line + 2) == ' ')
		make_sphere(vars, line + 2);
	else if (ft_strncmp(line, "pl", 2) == 0 && *(line + 2) == ' ')
		make_plane(vars, line + 2);
	else if (ft_strncmp(line, "cy", 2) == 0 && *(line + 2) == ' ')
		make_cylinder(vars, line + 2);
	else if (*line == '\n' && *(line + 1) == '\0')
		return ;
	else
		ft_error("File Format Error");
}

// double	parse_double(char *line)
// {

// }

// t_vec3	parse_vec(char *line)
// {

// }

static void	make_ambient(t_vars *vars, char *line)
{
	char	*tmp;
	int		i;

	// ratio
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]) || line[i] == '.')
		++i;
	tmp = ft_substr(line, 0, i);
	vars->ambient.lighting_ratio = ft_strtod(tmp);
	free(tmp);
	line += i;

	// r
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->ambient.rgb.x = ft_strtod(tmp);
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line == ',')
		++line;
	else
		ft_error("File Format Error");

	// g
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->ambient.rgb.y = ft_strtod(tmp);
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line == ',')
		++line;
	else
		ft_error("File Format Error");

	// b
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->ambient.rgb.z = ft_strtod(tmp);
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line != '\n')
		ft_error("File Format Error");

	vars->ambient.b_start = 1;
}

static void	make_camera(t_vars *vars, char *line)
{
	int		i;
	char	*tmp;

	// x
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->camera.view_point.x = ft_strtod(tmp); // FIXME: why exit
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line == ',')
		++line;
	else
		ft_error("File Format Error");

	// y
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->camera.view_point.y = ft_strtod(tmp);
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line == ',')
		++line;
	else
		ft_error("File Format Error");

	// z
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->camera.view_point.z = ft_strtod(tmp);
	free(tmp);
	line += i;
	if (*line != ' ')
		ft_error("File Format Error");

	// x
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->camera.direct_v.x = ft_strtod(tmp);
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line == ',')
		++line;
	else
		ft_error("File Format Error");

	// y
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->camera.direct_v.y = ft_strtod(tmp);
	free(tmp);
	line += i;
	while (*line == ' ')
		++line;
	if (*line == ',')
		++line;
	else
		ft_error("File Format Error");

	// z
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]))
		++i;
	tmp = ft_substr(line, 0, i);
	vars->camera.direct_v.z = ft_strtod(tmp);
	free(tmp);
	line += i;
	if (*line != ' ')
		ft_error("File Format Error");

	// fov
	while (*line == ' ')
		++line;
	i = 0;
	while (ft_isdigit(line[i]) || line[i] == '.')
		++i;
	tmp = ft_substr(line, 0, i);
	vars->ambient.lighting_ratio = ft_strtod(tmp);
	free(tmp);
	line += i;

	vars->camera.b_start = 1;
}
static void	make_light(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
}
static void	make_sphere(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
}
static void	make_plane(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
}
static void	make_cylinder(t_vars *vars, char *line)
{
	while (*line == ' ')
		line++;
}

static int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}

void static parse_test(t_vars *vars)
{
	printf("vars->ambient.lighting_ratio : %f\n", vars->ambient.lighting_ratio);
	printf("vars->ambient.color.r : %f\n", vars->ambient.rgb.x);
	printf("vars->ambient.color.g : %f\n", vars->ambient.rgb.y);
	printf("vars->ambient.color.b : %f\n", vars->ambient.rgb.z);

	printf("vars->camera.view_point.x : %f\n", vars->camera.view_point.x);
	printf("vars->camera.view_point.y : %f\n", vars->camera.view_point.y);
	printf("vars->camera.view_point.z : %f\n", vars->camera.view_point.z);
	printf("vars->camera.direct_v.x : %f\n", vars->camera.direct_v.x);
	printf("vars->camera.direct_v.y : %f\n", vars->camera.direct_v.y);
	printf("vars->camera.direct_v.z : %f\n", vars->camera.direct_v.z);
	printf("vars->camera.next->fov : %d\n", vars->camera.fov);

	printf("vars->light.brightness_ratio : %f\n", vars->light.brightness_ratio);
	printf("vars->light.light_point.x : %f\n", vars->light.light_point.x);
	printf("vars->light.light_point.y : %f\n", vars->light.light_point.y);
	printf("vars->light.light_point.z : %f\n", vars->light.light_point.z);
	printf("vars->light.rgb.x : %f\n", vars->light.rgb.x);
	printf("vars->light.rgb.y : %f\n", vars->light.rgb.y);
	printf("vars->light.rgb.z : %f\n", vars->light.rgb.z);
}
