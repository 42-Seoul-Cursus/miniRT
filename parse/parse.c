#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"
#include "../minirt.h"

#define TRUE 1
#define FALSE 0

static void	check_identifier(t_vars *vars, char *line);
double		parse_double(char **line);
t_vec3		parse_vec(char **line, int is_endl);
static void	make_ambient(t_vars *vars, char *line);
static void	make_camera(t_vars *vars, char *line);
static void	make_light(t_vars *vars, char *line);
static void	make_sphere(t_vars *vars, char *line);
static void	make_plane(t_vars *vars, char *line);
static void	make_cylinder(t_vars *vars, char *line);
static int	protected_open(char *path);

void	init_vars(t_vars *vars)
{
	vars->ambient.cnt = 0;
	vars->camera.cnt = 0;
	vars->light.cnt = 0;
	vars->objects = NULL;
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

static void	make_ambient(t_vars *vars, char *line)
{
	vars->ambient.lighting_ratio = parse_double(&line);
	vars->ambient.rgb = parse_vec(&line, TRUE);
	++(vars->ambient.cnt);
}

static void	make_camera(t_vars *vars, char *line)
{
	vars->camera.view_point = parse_vec(&line, FALSE);
	vars->camera.direct_v = parse_vec(&line, FALSE);
	vars->camera.fov = parse_double(&line);
	while (*line == ' ')
		line++;
	if (*line != '\n')
		ft_error("File Format Error");
	++(vars->camera.cnt);
}

static void	make_light(t_vars *vars, char *line)
{
	vars->light.light_point = parse_vec(&line, FALSE);
	vars->light.brightness_ratio = parse_double(&line);
	vars->light.rgb = parse_vec(&line, TRUE);
	++(vars->light.cnt);
}

static void	make_sphere(t_vars *vars, char *line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	sphere->center = parse_vec(&line, FALSE);
	sphere->diameter = parse_double(&line);
	sphere->radius = sphere->diameter / 2;
	sphere->rgb = parse_vec(&line, TRUE);
	ft_lstadd_back(&(vars->objects), ft_lstnew(sphere, SPHERE));
}

static void	make_plane(t_vars *vars, char *line)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	plane->point = parse_vec(&line, FALSE);
	plane->normal_v = parse_vec(&line, FALSE);
	plane->rgb = parse_vec(&line, TRUE);
	ft_lstadd_back(&(vars->objects), ft_lstnew(plane, PLANE));
}
static void	make_cylinder(t_vars *vars, char *line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	cylinder->center = parse_vec(&line, FALSE);
	cylinder->normal_v = parse_vec(&line, FALSE);
	cylinder->diameter = parse_double(&line);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = parse_double(&line);
	cylinder->rgb = parse_vec(&line, TRUE);
	ft_lstadd_back(&(vars->objects), ft_lstnew(cylinder, CYLINDER));
}

static int	protected_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error("Path Error");
	return (fd);
}
