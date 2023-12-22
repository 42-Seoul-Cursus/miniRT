/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 23:37:44 by sunko             #+#    #+#             */
/*   Updated: 2023/12/22 16:00:07 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WIDTH	1440
# define HEIGHT	920
# define IMG_RATIO	1.7778
# define SHIN_VALUE	64
# define SPEC_VALUE	0.5

typedef struct s_vec3			t_vec3;
typedef struct s_vec3			t_point3;
typedef struct s_vec3			t_color3;
typedef struct s_ambient		t_ambient;
typedef struct s_camera			t_camera;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_uvmap			t_uvmap;
typedef struct s_cylinder_cap	t_cylinder_cap;
typedef struct s_cylinder		t_cylinder;
typedef struct s_mlx_data		t_mlx_data;
typedef struct s_mlx_args		t_mlx_args;
typedef struct s_vars			t_vars;
typedef struct s_vec4			t_vec4;
typedef struct s_4x4matrix		t_4x4matrix;
typedef struct s_ray			t_ray;
typedef struct s_hit_record		t_hit_record;
typedef struct s_light			t_light;
typedef struct s_list			t_list;

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
	t_color3	i_rgb;
	t_color3	r_rgb;
	int			cnt;
};

struct s_camera
{
	t_point3	view_point;
	t_vec3		direct_v;
	t_vec3		up_v;
	t_vec3		euler_angles;
	double		fov;
	double		fov_len;
	double		viewport_width;
	double		viewport_height;
	t_vec3		viewport_u;
	t_vec3		viewport_v;
	t_vec3		pixel_delta_u;
	t_vec3		pixel_delta_v;
	t_vec3		viewport_upper_left;
	t_vec3		pixel_00_loc;
	int			cnt;
};

struct s_light
{
	t_point3	light_point;
	double		brightness_ratio;
	t_color3	i_rgb;
	t_color3	r_rgb;
};

/*
struct s_textmap
{
	t_text_data	texture;
	t_text_data	normal;
}

struct s_text_data
{
	char	*path;
	void	*addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}
*/
// s_uvmap => s_check_map

struct s_uvmap
{
	t_color3	rgb1;
	t_color3	rgb2;
	int			width;
	int			height;
	int			cnt;
};

struct s_sphere
{
	t_point3	center;
	double		diameter;
	double		radius;
	t_color3	i_rgb;
	t_color3	r_rgb;
};

struct s_plane
{
	t_point3	point;
	t_vec3		normal_v;
	t_color3	i_rgb;
	t_color3	r_rgb;
};

struct s_cylinder
{
	t_point3	center;
	t_vec3		normal_v;
	double		diameter;
	double		radius;
	double		height;
	t_color3	i_rgb;
	t_color3	r_rgb;
	t_plane		top;
	t_plane		bottom;
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

struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

/*
p: 맞은 점의 위치
normal: 맞은 점의 노말 벡터
tmin: 카메라의 뒤에 있는 지 확인
tmax: 이미 맞은 (이제 그릴)오브젝트보다 뒤에 있는 지 확인
t: p_o + vt에서 t
front_face : 광선의 방향벡터와 교점의 법선벡터의 내적이
음수라면 광선은 앞면에 hit한 것이다.
 */
struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	int			front_face;
	t_color3	color;
};

struct s_vars
{
	t_ambient		ambient;
	t_camera		camera;
	t_list			*light;
	t_uvmap			uvmap;
	t_list			*objects;
	t_ray			ray;
	t_hit_record	rec;
	t_mlx_data		mlx_data;
	t_mlx_data		texture;
	t_mlx_data		normal;
	int				t_width;
	int				t_height;
	int				n_width;
	int				n_height;
};

struct s_4x4matrix
{
	t_vec4	r1;
	t_vec4	r2;
	t_vec4	r3;
	t_vec4	r4;
};

enum	e_type
{
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT_POINT
};

struct s_list
{
	void			*content;
	enum e_type		type;
	struct s_list	*next;
};

#endif
