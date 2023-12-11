/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:42:50 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 16:42:54 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "libft.h"
#include "matrix.h"

double	*get_move_matrix(t_point3 p)
{
	double	m[4][4];

	ft_bzero(&m, sizeof(double) * 16);
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
	m[0][3] = -p.x;
	m[1][3] = -p.y;
	m[2][3] = -p.z;
	return (m);
}

double	*get_rotate_matrix(t_vec3 x, t_vec3 y, t_vec3 z)
{
	double	m[4][4];

	ft_bzero(&m, sizeof(double) * 16);
	m[0][0] = x.x;
	m[0][1] = x.y;
	m[0][2] = x.z;
	m[1][0] = y.x;
	m[1][1] = y.y;
	m[1][2] = y.z;
	m[2][0] = z.x;
	m[2][1] = z.y;
	m[2][2] = z.z;
	m[3][3] = 1;
	return (m);
}

t_point3	mp_mul(const double **m, t_point3 p)
{
	int			i;
	int			j;
	double		p2m[4];
	double		m_rst[4];
	t_point3	rst;

	i = -1;
	j = -1;
	p2m[0] = p.x;
	p2m[1] = p.y;
	p2m[2] = p.z;
	p2m[3] = 1;
	while (++i < 4)
	{
		while (++j < 4)
			m_rst[i] += m[i][j] * p2m[j];
		i++;
	}
	rst.x = m_rst[0];
	rst.y = m_rst[1];
	rst.z = m_rst[2];
	return (rst);
}
