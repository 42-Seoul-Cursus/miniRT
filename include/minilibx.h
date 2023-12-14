#ifndef MINILIBX_H
# define MINILIBX_H

# include "structures.h"

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			open_window(void);
int			create_trgb(int t, int r, int g, int b);
int			exit_hook(void);
int			key_hook(int keycode, t_vars *vars);

#endif
