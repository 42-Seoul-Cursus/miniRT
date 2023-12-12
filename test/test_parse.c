#include "test.h"

void	test_parse(t_vars *vars)
{
	// ambient
	printf("A %.1f %.1f,%.1f,%.1f\n", vars->ambient.lighting_ratio, vars->ambient.rgb.x, vars->ambient.rgb.y, vars->ambient.rgb.z);
	printf("\n");

	// camera
	printf("C %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f\n", vars->camera.view_point.x, vars->camera.view_point.y, vars->camera.view_point.z, vars->camera.direct_v.x, vars->camera.direct_v.y, vars->camera.direct_v.z, vars->camera.fov);

	// light
	printf("L %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f\n", vars->light.light_point.x, vars->light.light_point.y, vars->light.light_point.z, vars->light.brightness_ratio, vars->light.rgb.x, vars->light.rgb.y, vars->light.rgb.z);
	printf("\n");

	// objects Verify identifiers
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_list		*tmp;

	tmp = vars->objects;
	while (tmp)
	{
		printf("type: %d\n", tmp->type);
		tmp = tmp->next;
	}

	tmp = vars->objects;

	// PLANE
	plane = tmp->content;
	printf("pl %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f,%.1f,%.1f\n", plane->point.x, plane->point.y, plane->point.z, plane->normal_v.x, plane->normal_v.y, plane->normal_v.z, plane->rgb.x, plane->rgb.y, plane->rgb.z);
	tmp = tmp->next;

	// SPHERE
	sphere = tmp->content;
	printf("sp %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f\n", sphere->center.x, sphere->center.y, sphere->center.z, sphere->diameter, sphere->rgb.x, sphere->rgb.y, sphere->rgb.z);
	tmp = tmp->next;

	// CYLINDER
	cylinder = tmp->content;
	printf("cy %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f %.1f %.1f,%.1f,%.1f\n", cylinder->center.x, cylinder->center.y, cylinder->center.z, cylinder->normal_v.x, cylinder->normal_v.y, cylinder->normal_v.z, cylinder->diameter, cylinder->height, cylinder->rgb.x, cylinder->rgb.y, cylinder->rgb.z);
	tmp = tmp->next;

	printf("%p\n", tmp);
}
