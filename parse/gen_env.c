#include "../minirt.h"

void	gen_ambient(t_vars *vars, char *line)
{
	vars->ambient.lighting_ratio = parse_double(&line);
	vars->ambient.rgb = parse_vec(&line, TRUE);
	++(vars->ambient.cnt);
}

void	gen_camera(t_vars *vars, char *line)
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

void	gen_light(t_vars *vars, char *line)
{
	vars->light.light_point = parse_vec(&line, FALSE);
	vars->light.brightness_ratio = parse_double(&line);
	vars->light.rgb = parse_vec(&line, TRUE);
	++(vars->light.cnt);
}
