/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:27:59 by sunko             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/11 16:12:14 by sunko            ###   ########.fr       */
=======
/*   Updated: 2023/12/11 16:34:25 by seunan           ###   ########.fr       */
>>>>>>> a42cc170d1dfede14e28fcc5c7ddfbe3a87f5c38
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structures.h"

void	init_mlx(t_mlx_data *mlx_data);
void	execute_mlx(t_mlx_data *mlx_data);

/* parse */

// parse.c
void	init_vars(t_vars *vars);
void	parse_rt(t_vars *vars, char *path);

// check_arg.c
void	is_valid_arg(int ac, char *av[]);


#endif
