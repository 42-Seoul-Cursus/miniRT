/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/22 16:08:02 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "render.h"
#include "utils.h"
#include "mlx.h"

int	main(int argc, char *argv[])
{
	t_vars		vars;

	is_valid_arg(argc, argv);
	init_vars(&vars);
	parse_rt(&vars, argv[1]);
	init_mlx(&vars.mlx_data);
	vars.texture.img = mlx_xpm_file_to_image(vars.mlx_data.mlx, "./maps/white.xpm", &vars.t_width, &vars.t_height);
	vars.normal.img = mlx_xpm_file_to_image(vars.mlx_data.mlx, "./maps/sofa_n.xpm", &vars.n_width, &vars.n_height);
	vars.texture.addr = mlx_get_data_addr(vars.texture.img, &vars.texture.bits_per_pixel, &vars.texture.line_length, &vars.texture.endian);
	vars.normal.addr = mlx_get_data_addr(vars.normal.img, &vars.normal.bits_per_pixel, &vars.normal.line_length, &vars.normal.endian);
	world2view(&vars);
	render(&vars);
	execute_mlx(&vars);
	return (0);
}
