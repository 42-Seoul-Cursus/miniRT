/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:18:07 by sunko             #+#    #+#             */
/*   Updated: 2023/12/18 00:21:23 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "structures.h"

t_ray		ray(t_point3 orig, t_vec3 dir);
t_point3	ray_at(t_ray *ray, const double t);

int			hit_sphere(\
t_sphere *sphere, t_ray *ray, t_hit_record *rec, t_uvmap *uv);
int			hit_plane(\
t_plane *plane, t_ray *ray, t_hit_record *rec, t_uvmap *uv);
t_color3	execute_phong(t_vars *vars);

int			hit_obj(t_list *object, t_ray *ray, t_hit_record *rec, t_uvmap *uv);
int			hit(t_list *objects, t_ray *ray, t_hit_record *rec, t_uvmap *uv);
int			in_shadow(t_list *object, t_ray ray, double light_len, t_uvmap *uv);
t_color3	ray_color(t_vars *vars);

#endif
