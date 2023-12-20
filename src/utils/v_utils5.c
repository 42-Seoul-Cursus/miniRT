/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_utils5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:17:45 by sunko             #+#    #+#             */
/*   Updated: 2023/12/20 15:19:21 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "structures.h"

t_vec3	vec4_to_vec3(t_vec4 v4)
{
	return (vec3(v4.x, v4.y, v4.z));
}
