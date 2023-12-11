/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:12:37 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 16:13:05 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

double	*get_move_matrix(t_point3 p);
double	*get_rotate_matrix(t_vec3 x, t_vec3 y, t_vec3 z);

#endif
