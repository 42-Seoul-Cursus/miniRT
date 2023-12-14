/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:18:07 by sunko             #+#    #+#             */
/*   Updated: 2023/12/14 20:26:07 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structures.h"

t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, const double t);

int			hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec);

t_color3	execute_phong(t_vars *vars);
int			in_shadow(t_list *object, t_ray ray, double light_len);

int			hit_obj(t_list *object, t_ray *ray, t_hit_record *rec);
int			hit(t_list *objects, t_ray *ray, t_hit_record *rec);
int			in_shadow(t_list *object, t_ray ray, double light_len);
t_color3	ray_color(t_vars *vars);


#endif
