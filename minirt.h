/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:27:59 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 15:09:48 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structures.h"

void	init_mlx(t_mlx_data *mlx_data);
void	execute_mlx(t_mlx_data *mlx_data);

/* parse */

// check_arg.c
void	is_valid_arg(int ac, char *av[]);


#endif
