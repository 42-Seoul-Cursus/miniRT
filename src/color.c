#include "structures.h"

t_color3	 get_color_int_to_real(t_color3 rgb)
{
	t_color3	out;

	out.x = rgb.x / 255;
	out.y = rgb.y / 255;
	out.z = rgb.z / 255;
	return (out);
}

t_color3	get_color_real_to_int(t_color3 rgb)
{
	t_color3	out;

	out.x = rgb.x * 255;
	out.y = rgb.y * 255;
	out.z = rgb.z * 255;
	return (out);
}
