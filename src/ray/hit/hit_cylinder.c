/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:03:51 by seunan            #+#    #+#             */
/*   Updated: 2023/12/17 23:56:38 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ray.h"
#include <math.h>

static int	hit_cylinder_cap(t_plane *cap, double radius, t_ray *ray, t_hit_record *rec);
static int	hit_cylinder_body(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);

int	hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	if (hit_cylinder_cap(&cylinder->top, cylinder->radius, ray, rec))
		return (1);
	if (hit_cylinder_cap(&cylinder->bottom, cylinder->radius, ray, rec))
		return (1);
	if (hit_cylinder_body(cylinder, ray, rec))
		return (1);
	return (0);
}

static int	hit_cylinder_body(t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	b;
	double	c;
	double	oc;

	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	b = 2 * (ray->orig.x * ray->dir.x + ray->orig.z * ray->dir.z - \
		cylinder->center.x * ray->dir.x - cylinder->center.z * ray->dir.z);
	c = ray->orig.x * ray->orig.x + cylinder->center.x * cylinder->center.x + \
		ray->orig.z * ray->orig.z + cylinder->center.z * cylinder->center.z \
		- 2 * (ray->orig.x * cylinder->center.x + ray->orig.z * cylinder->center.z) \
		- cylinder->radius * cylinder->radius;
	oc = b * b - 4 * a * c;
	if (oc < 10e-4)
		return (0);

	double	t1;
	double	t2;
	double	t;
	double	r;

	t1 = (-b - sqrt(oc)) / (2 * a);
	t2 = (-b + sqrt(oc)) / (2 * a);
	if (t1 > t2)
		t = t2;
	else
		t = t1;
	r = ray->orig.y + t * ray->dir.y;
	if (!(cylinder->center.y - cylinder->height <= r && r <= cylinder->center.y + cylinder->height))
		return (0);
	rec->t = t;
	rec->color = cylinder->r_rgb;
	rec->p = ray_at(ray, t);
	rec->normal = cylinder->normal_v;
	return (1);
}

static int	hit_cylinder_cap(t_plane *cap, double radius, t_ray *ray, t_hit_record *rec)
{
	if (hit_plane(cap, ray, rec))
	{
		t_vec3	p = v_plus(ray->orig, vt_mul(ray->dir, rec->t));
		t_vec3	v = v_minus(p, cap->normal_v);
		double	d2 = v_dot(v, v);
		if (sqrt(d2) > radius)
			return (0);
		rec->color = cap->r_rgb;
		rec->p = p;
		rec->normal = cap->normal_v;
		return (1);
	}
	return (0);
}

/*
The ray-disk intersection routine is very simple.
A disk is generally defined by a position (the disk center's position), a normal, and a radius.
First, we can test if the ray intersects the plane in which lies the disk.
For the ray-plane intersection step, we can use the code we have developed for the ray-plane intersection test.
If the ray intersects this plane, all we have to do is calculate the intersection point and the distance from this point to this disk's center.
The ray intersects the disk if this distance is lower or equal to the disk radius.
Note that as an optimization, you can test the square of the distance against the square of the disk's radius.
The square distance can be calculated from the dot product of this vector (v in the code) with itself.
Technically, computing the distance would require taking the square root of this dot product.
However, we can also test the result of this dot product directly against the square of the radius (which is generally precomputed) to avoid using an expensive square root operation.

bool intersectDisk(const Vec3f &n, const Vec3f &p0, const float &radius, const Vec3f &l0, const Vec3 &l)
{
	float t = 0;
	if (intersectPlane(n, p0, l0, l, t)) {
		Vec3f p = l0 + l * t;
		Vec3f v = p - p0;
		float d2 = dot(v, v);
		return (sqrtf(d2) <= radius);
		// or you can use the following optimization (and precompute radius^2)
		// return d2 <= radius2; // where radius2 = radius * radius
	 }

	 return false;
}

intersectDisk 함수는 다음과 같은 입력 매개변수를 사용합니다:

n: 디스크의 법선 벡터.
p0: 디스크 중심의 위치 벡터.
radius: 디스크의 반지름.
l0: 광선의 원점.
l: 광선의 방향 벡터.
코드는 먼저 광선이 디스크가 속한 평면과 교차하는지 여부를 intersectPlane 함수를 사용하여 확인합니다. 이 교차 여부의 결과는 변수 t에 저장됩니다.

광선이 평면과 교차한다면, 코드는 교차점 p를 계산합니다. 이는 p = l0 + l * t와 같은 공식을 사용합니다.

벡터 v는 디스크 중심 p0에서 교차점 p로 향하는 벡터로 계산됩니다.

거리의 제곱인 d2는 dot(v, v)를 사용하여 계산됩니다.

코드는 이 거리의 제곱이 디스크의 반지름의 제곱과 작거나 같은지 확인합니다. 이는 제곱근 연산을 피하기 위한 최적화입니다. 광선이 디스크와 교차한다면 true를 반환합니다.

함수는 광선이 디스크와 교차하지 않으면 false를 반환합니다.

이 코드는 광선이 디스크와 교차하는지 여부를 판별하는데 사용되며, 제곱근 연산을 최소화하여 계산 성능을 향상시킵니다.
*/
