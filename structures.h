/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:37:44 by sunko             #+#    #+#             */
/*   Updated: 2023/12/12 22:51:02 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libft/libft.h"

# define WIDTH	1920
# define HEIGHT	1080
# define IMG_RATIO	1.7778

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
typedef struct s_vec4		t_vec4;
typedef struct s_4x4matrix	t_4x4matrix;
typedef struct s_ray		t_ray;
struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
};

struct s_ambient
{
	double		lighting_ratio;
	t_color3	rgb;
	int			cnt;
};

struct s_camera
{
	t_point3	view_point;
	t_vec3		direct_v;
	double		fov;
	double		fov_len;
	double		viewport_width;
	double		viewport_height;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_vec3		viewport_upper_left;
	t_vec3		poxel_00_loc;
	int			cnt;
};

struct s_light
{
	t_point3	light_point;
	double		brightness_ratio;
	t_color3	rgb;
	int			cnt;
};

struct s_sphere
{
	t_point3	center;
	double		diameter;
	double		radius;
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

struct s_vars
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
};

struct s_4x4matrix
{
	t_vec4	r1;
	t_vec4	r2;
	t_vec4	r3;
	t_vec4	r4;
};

struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

#endif
