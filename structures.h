/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:37:44 by sunko             #+#    #+#             */
/*   Updated: 2023/12/10 23:51:19 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_mlx_data	t_mlx_data;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ambient
{
	double	lighting_ratio;
};

struct s_camera
{
	t_point3	view_point;
	t_vec3		direct_v;
	int			fov;
};

struct s_light
{
	t_point3	light_point;
	double		brightness_ratio;
	t_color3	rgb;
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		diameter;
	t_color3	rgb;
};

struct s_plane
{
	t_point3	point;
	t_vec3		normal_v;
	t_color3	rgb;
};

struct s_cylinder
{
	t_point3	center;
	t_vec3		normal_v;
	double		diameter;
	double		radius;
	double		height;
	t_color3	rgb;
};

enum
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

struct s_mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

#endif
