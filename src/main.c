/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/13 21:11:37 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* TEST */
#include "test.h"
/* TEST */

#include "minirt.h"
#include "parse.h"
#include "vector.h"

int	main(int argc, char *argv[])
{
	atexit(leak);
	t_mlx_data	mlx_data;
	t_vars		vars;

	is_valid_arg(argc, argv);
	init_vars(&vars);
	parse_rt(&vars, argv[1]);
	test_parse(&vars);
	init_mlx(&mlx_data);
	world2view(&vars);
	render(&vars, &mlx_data);
	execute_mlx(&mlx_data, &vars);
	return (0);
}
