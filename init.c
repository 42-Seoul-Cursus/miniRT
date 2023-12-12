#include "minirt.h"
#include <stdlib.h>

void	init_vars(t_vars *vars)
{
	vars->ambient.cnt = 0;
	vars->camera.cnt = 0;
	vars->light.cnt = 0;
	vars->objects = NULL;
}
