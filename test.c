#include <stdio.h>
#include "structures.h"

void	parse_test(t_vars *vars)
{
	// Ambient
	t_ambient	ambient = vars->ambient;
	printf("A %.1f %.1f,%.1f,%.1f\n", ambient.lighting_ratio, ambient.i_rgb.x, ambient.i_rgb.y, ambient.i_rgb.z);

	// Camera
	t_camera	camera = vars->camera;
	printf("C %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f\n", camera.view_point.x, camera.view_point.y, camera.view_point.z, camera.direct_v.x, camera.direct_v.y, camera.direct_v.z, camera.fov);

	// Lights
	t_list		*cur = vars->light;
	while (cur)
	{
		printf("L %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f\n", ((t_light *)cur->content)->light_point.x, ((t_light *)cur->content)->light_point.y, ((t_light *)cur->content)->light_point.z, ((t_light *)cur->content)->brightness_ratio, ((t_light *)cur->content)->i_rgb.x, ((t_light *)cur->content)->i_rgb.y, ((t_light *)cur->content)->i_rgb.z);
		cur = cur->next;
	}

	// Objects
	cur = vars->objects;
	while (cur)
	{
		if (cur->type == SPHERE)
		{
			printf("sp %.1f,%.1f,%.1f %.1f %.1f,%.1f,%.1f ", ((t_sphere *)cur->content)->center.x, ((t_sphere *)cur->content)->center.y, ((t_sphere *)cur->content)->center.z, ((t_sphere *)cur->content)->radius * 2, ((t_sphere *)cur->content)->i_rgb.x, ((t_sphere *)cur->content)->i_rgb.y, ((t_sphere *)cur->content)->i_rgb.z);
			if (((t_sphere *)cur->content)->checker != NULL)
				printf("chk %.1f,%.1f,%.1f %.1f,%.1f,%.1f %d %d", ((t_sphere *)cur->content)->checker->rgb1.x, ((t_sphere *)cur->content)->checker->rgb1.y, ((t_sphere *)cur->content)->checker->rgb1.z, ((t_sphere *)cur->content)->checker->rgb2.x, ((t_sphere *)cur->content)->checker->rgb2.y, ((t_sphere *)cur->content)->checker->rgb2.z, ((t_sphere *)cur->content)->checker->width, ((t_sphere *)cur->content)->checker->height);
			if (((t_sphere *)cur->content)->uvmap != NULL)
				printf("%s %s", ((t_sphere *)cur->content)->uvmap->texture->path, ((t_sphere *)cur->content)->uvmap->normal->path);
			printf("\n");
		}
		if (cur->type == PLANE)
		{
			printf("pl %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f,%.1f,%.1f ", ((t_plane *)cur->content)->point.x, ((t_plane *)cur->content)->point.y, ((t_plane *)cur->content)->point.z, ((t_plane *)cur->content)->normal_v.x, ((t_plane *)cur->content)->normal_v.y, ((t_plane *)cur->content)->normal_v.z, ((t_plane *)cur->content)->i_rgb.x, ((t_plane *)cur->content)->i_rgb.y, ((t_plane *)cur->content)->i_rgb.z);
			if (((t_plane *)cur->content)->checker != NULL)
				printf("chk %.1f,%.1f,%.1f %.1f,%.1f,%.1f %d %d", ((t_plane *)cur->content)->checker->rgb1.x, ((t_plane *)cur->content)->checker->rgb1.y, ((t_plane *)cur->content)->checker->rgb1.z, ((t_plane *)cur->content)->checker->rgb2.x, ((t_plane *)cur->content)->checker->rgb2.y, ((t_plane *)cur->content)->checker->rgb2.z, ((t_plane *)cur->content)->checker->width, ((t_plane *)cur->content)->checker->height);
			if (((t_plane *)cur->content)->uvmap != NULL)
				printf("%s %s", ((t_plane *)cur->content)->uvmap->texture->path, ((t_plane *)cur->content)->uvmap->normal->path);
			printf("\n");
		}
		if (cur->type == CYLINDER)
		{
			printf("cy %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f %.1f %.1f,%.1f,%.1f ", ((t_cylinder *)cur->content)->center.x, ((t_cylinder *)cur->content)->center.y,((t_cylinder *)cur->content)->center.z,((t_cylinder *)cur->content)->normal_v.x, ((t_cylinder *)cur->content)->normal_v.y,((t_cylinder *)cur->content)->normal_v.z, ((t_cylinder *)cur->content)->radius * 2, ((t_cylinder *)cur->content)->height, ((t_cylinder *)cur->content)->i_rgb.x, ((t_cylinder *)cur->content)->i_rgb.y, ((t_cylinder *)cur->content)->i_rgb.z);
			if (((t_cylinder *)cur->content)->checker != NULL)
				printf("chk %.1f,%.1f,%.1f %.1f,%.1f,%.1f %d %d", ((t_cylinder *)cur->content)->checker->rgb1.x, ((t_cylinder *)cur->content)->checker->rgb1.y, ((t_cylinder *)cur->content)->checker->rgb1.z, ((t_cylinder *)cur->content)->checker->rgb2.x, ((t_cylinder *)cur->content)->checker->rgb2.y, ((t_cylinder *)cur->content)->checker->rgb2.z, ((t_cylinder *)cur->content)->checker->width, ((t_cylinder *)cur->content)->checker->height);
			if (((t_cylinder *)cur->content)->uvmap != NULL)
				printf("%s %s", ((t_cylinder *)cur->content)->uvmap->texture->path, ((t_cylinder *)cur->content)->uvmap->normal->path);
			printf("\n");
		}
		cur = cur->next;
	}
	
}
