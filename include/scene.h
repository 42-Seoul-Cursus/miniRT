#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_canvas	make_canvas(int  width, int height);
t_camera	make_camera(t_canvas *canvas, t_point3 origin);
t_sphere	*make_sphere(t_point3 center, double radius);
t_light		*make_light(t_point3 light_origin, t_color3 light_color, double bright_ratio);
t_object	*make_object(t_type type, void *element, t_color3 albedo);

#endif
