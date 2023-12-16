/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/16 15:41:06 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

/*
std::vector<tuple<Point, double, bool>> intersections; (intersection point, distance from light source, is on the cylinder's side ?)
	double e = 0.00001;
	Vector da = ray.D - ray.D.dot(axis)*axis; //used for less calculations
	Vector dp = ray.O - c1; //used for less calculations
	Vector db = dp - (dp.dot(axis)*axis); //used for less calculations
	double A = da.length_2();
	double B = 2 * (da.dot(db));
	double C = db.length_2()-pow(radius, 2);
*/

/*
무한 단위 실린더는 z축을 따라 정렬되어 다음과 같이 정의된다.
x^2 + y^2 = r^2. r = 1

(Xo + tXd)^2 + (Yo + tYd)^2 = 1
=> t^2(Xd^2 + Yd^2) + 2t(XoXd + YoYd) + (Xo^2 + Yo^2 - 1) = 0
=> at^2 + bt + c = 0
=> t = (-b +- sqrt(b^2 - 4ac)) / 2a

a = Xd^2 + Yd^2
b = 2(XoXd + YoYd)
c = Xo^2 + Yo^2 - 1
ray와 이 실린더의 교점을 찾는다.

v(t) = ray.orig + t * ray.dir 에 대해
t >= 0 이고 교점이 두 개이며, 두 교점이 실린더의 높이 범위 내에 있어야 한다.
*/

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	double	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	double	b = 2 * (ray->orig.x * ray->dir.x + ray->orig.z * ray->dir.z);
	double	c = ray->orig.x * ray->orig.x + ray->orig.z * ray->orig.z - cylinder->radius * cylinder->radius;

	double	oc = b * b - 4 * a * c;
	if (oc < -10e-4)
		return (0);
	double	t1 = (-b - sqrt(oc)) / (2 * a); // t의 두 근
	double	t2 = (-b + sqrt(oc)) / (2 * a); // t의 두 근
	double	t;
	if (t1 > t2)
		t = t2;
	else
		t = t1;
	double r = ray->orig.y + t * ray->dir.y;
	if (!(cylinder->center.y - cylinder->height <= r && r <= cylinder->center.y + cylinder->height))
		return (0);
	rec->t = t;
	rec->color = cylinder->r_rgb;
	rec->p = ray_at(ray, t);
	rec->normal = cylinder->normal_v;
	return (1);
}
