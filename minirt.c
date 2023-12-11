/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:23:22 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 14:42:37 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structures.h"
#include "libft.h"
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_mlx_data	mlx_data;

	is_valid_arg(argc, argv);
	init_mlx(&mlx_data);
	execute_mlx(&mlx_data);
	return (0);
}
