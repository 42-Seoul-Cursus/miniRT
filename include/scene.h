#ifndef SCENE_H
# define SCENE_H

# include "structures.h"
# include "utils.h"

t_canvas	make_canvas(int  width, int height);
t_camera	make_camera(t_canvas *canvas, t_point3 origin);
t_sphere	make_sphere(t_point3 center, double radius);

#endif
