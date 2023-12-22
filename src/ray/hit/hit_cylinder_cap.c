/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_cap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:02:36 by seunan            #+#    #+#             */
/*   Updated: 2023/12/21 16:14:40 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"

/*
두 개의 레이가 hit 함수로 들어옴
1. 카메라 레이
2. 쉐도우 판정 레이

hit_cylinder에서 body부터 확인하고 return하기 때문에 바닥이 보이지 않음
temp_rec에 미리 저장하고 판정 다시 해야함
*/
int	hit_cylinder_bottom(t_cylinder *cylinder, t_ray *ray, \
	t_hit_record *rec)
{
	t_plane			cap;
	t_point3		p;
	double			radius2;

	radius2 = cylinder->radius * cylinder->radius;
	cap = cylinder->bottom;
	if (hit_plane(&cap, ray, rec))
	{
		p = v_minus(rec->p, cap.point);
		if (v_dot(p, p) <= radius2)
			return (1);
	}
	return (0);
}

int	hit_cylinder_top(t_cylinder *cylinder, t_ray *ray, \
	t_hit_record *rec)
{
	t_plane			cap;
	t_point3		p;
	double			radius2;

	radius2 = cylinder->radius * cylinder->radius;
	cap = cylinder->top;
	if (hit_plane(&cap, ray, rec))
	{
		p = v_minus(rec->p, cap.point);
		if (v_dot(p, p) <= radius2)
			return (1);
	}
	return (0);
}
