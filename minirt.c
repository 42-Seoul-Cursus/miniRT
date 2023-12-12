/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 17:55:45 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;
	t_vars		vars;

	is_valid_arg(argc, argv);
	init_vars(&vars);
	parse_rt(&vars, argv[1]);
	is_valid_rt(&vars);
	init_mlx(&mlx_data);
	world2view(&vars);
	execute_mlx(&mlx_data);
	return (0);
}
