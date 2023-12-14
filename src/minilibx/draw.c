#include "structures.h"

int	create_trgb(int t, t_color3 color)
{
	int r;
	int g;
	int b;

	r = color.x * 255.999;
	g = color.y * 255.999;
	b = color.z * 255.999;
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// line_length는 픽셀의 한 줄의 바이트 수이므로 y * line_length는 y번째 줄의 시작 주소를 의미한다.
	// bits_per_pixel은 픽셀의 비트 수이므로 x * (bits_per_pixel / 8)은 x번째 픽셀의 시작 주소를 의미한다.
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
