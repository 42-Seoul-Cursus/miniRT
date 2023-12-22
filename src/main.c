/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/22 20:44:00 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "render.h"
#include "utils.h"
#include "mlx.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	is_valid_arg(argc, argv);
	init_vars(&vars);
	init_mlx(&vars.mlx_data);
	parse_rt(&vars, argv[1]);
	world2view(&vars);
	render(&vars);
	execute_mlx(&vars);
	return (0);
}
