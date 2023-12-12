/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:59:56 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 13:59:59 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdlib.h>

void	init_vars(t_vars *vars)
{
	vars->ambient.cnt = 0;
	vars->camera.cnt = 0;
	vars->light.cnt = 0;
	vars->objects = NULL;
}
