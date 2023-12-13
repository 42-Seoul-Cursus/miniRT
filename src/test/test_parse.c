#include "test.h"

void	test_parse(t_vars *vars)
{
	t_list		*tmp;
	t_light		*light;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	// ambient
	printf("A %.1f %.1f,%.1f,%.1f\n", vars->ambient.lighting_ratio, vars->ambient.rgb.x, vars->ambient.rgb.y, vars->ambient.rgb.z);
	printf("\n");

	// camera
	printf("C %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f\n", vars->camera.view_point.x, vars->camera.view_point.y, vars->camera.view_point.z, vars->camera.direct_v.x, vars->camera.direct_v.y, vars->camera.direct_v.z, vars->camera.fov);

	// light
	tmp = vars->light;
	while (tmp != NULL)
	{
		light = tmp->content;
		printf("L %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f\n", light->light_point.x, light->light_point.y, light->light_point.z, light->brightness_ratio, light->rgb.x, light->rgb.y, light->rgb.z);
		tmp = tmp->next;
	}
	printf("\n");

	// objects Verify identifiers
	tmp = vars->objects;
	while (tmp != NULL)
	{
		if (tmp->type == PLANE)
		{
			plane = tmp->content;
			printf("pl %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f,%.1f,%.1f\n", plane->point.x, plane->point.y, plane->point.z, plane->normal_v.x, plane->normal_v.y, plane->normal_v.z, plane->rgb.x, plane->rgb.y, plane->rgb.z);
		}
		else if (tmp->type == SPHERE)
		{
			sphere = tmp->content;
			printf("sp %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f\n", sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter, sphere->rgb.x, sphere->rgb.y, sphere->rgb.z);
		}
		else if (tmp->type == CYLINDER)
		{
			cylinder = tmp->content;
			printf("cy %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f %.1f %.1f,%.1f,%.1f\n", cylinder->center.x, cylinder->center.y, cylinder->center.z, cylinder->normal_v.x, cylinder->normal_v.y, cylinder->normal_v.z, cylinder->diameter, cylinder->height, cylinder->rgb.x, cylinder->rgb.y, cylinder->rgb.z);
		}
		tmp = tmp->next;
	}
}
