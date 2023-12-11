/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:37:44 by sunko             #+#    #+#             */
/*   Updated: 2023/12/11 16:35:03 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft/libft.h"

typedef struct s_vec3		t_vec3;
typedef struct s_vec3		t_point3;
typedef struct s_vec3		t_color3;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_vars		t_vars;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_ambient
{
	double		lighting_ratio;
	t_color3	rgb;
	int			b_start;
};

struct s_camera
{
	t_point3	view_point;
	t_vec3		direct_v;
	int			fov;
	int			b_start;
};

struct s_light
{
	t_point3	light_point;
	double		brightness_ratio;
	t_color3	rgb;
	int			b_start;
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		diameter;
	t_color3	rgb;
	int			b_start;
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

struct s_vars
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		objects;
};

#endif
