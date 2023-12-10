/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/10 23:48:44 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structures.h"
#include "libft.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nInvaild number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	init_mlx(&mlx_data);
	execute_mlx(&mlx_data);
	return (0);
}
