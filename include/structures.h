#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WIDTH 1440
# define HEIGHT 900

# define EPSILON 1e-6 // 0.000001

# define LUMEN 3  // 이 값을 조절하여 장면의 밝기를 조절할 수 있다.

typedef enum e_bool t_bool;
typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_hit_record t_hit_record;

typedef enum e_type t_type;
typedef struct s_object t_object;
typedef struct s_sphere t_sphere;
typedef struct s_light t_light;

typedef struct s_scene t_scene;

typedef struct s_vars t_vars;
typedef struct s_data t_data;

enum e_bool
{
	FALSE = 0,
	TRUE = 1
};

struct s_vec3
{
	double x;
	double y;
	double z;
};

struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct  s_camera
{
	t_point3	orig;  // 카메라 원점(위치)
	double		viewport_h; // 뷰포트 세로길이
	double		viewport_w; // 뷰포트 가로길이
	t_vec3		horizontal; // +x축 방향 크기가 viewport_width인 벡터
	t_vec3		vertical; // +y축 방향 크기가 viewport_height인 벡터
	double		focal_len; // focal length
	t_point3	left_bottom; // 왼쪽 아래 코너점, 이 점을 기준으로 u, v 만큼 올라간 곳에 픽셀을 그린다.
};

struct  s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
};

// P(t) = O + tD
// P(t) : 광선의 원점에서 t만큼 떨어진 점
// O : 광선의 원점
// D : 광선의 방향벡터
// t : 광선의 원점에서 교점까지의 거리
struct s_hit_record
{
	t_point3	p; // 교점의 좌표
	t_vec3		normal; // 교점에서의 법선
	double		tmin; // 오브젝트가 카메가의 뒤에 있을 때를 고려하기 위한 변수
	double		tmax; // 오브젝트가 카메라로부터 너무 멀 경우 고려하기 위한 변수
	double		t; // 광선의 원점과 교점 사이의 거리
	t_bool		front_face;
	t_color3	albedo;
};

enum e_type
{
	SPHERE,
	LIGHT,
};

struct s_object
{
	t_type		type;
	void		*element;
	t_color3	albedo;
	void		*next;
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct s_light
{
	t_point3	orig;
	t_color3	color;
	double		bright_ratio;
};

struct  s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_color3		ambient;
	t_ray			ray;
	t_hit_record	rec;
};


/* MLX STRUCTURES */

// mlx 구조체
struct s_vars
{
	void	*mlx; // 그래픽 시스템에 대한 연결 설정을 위한 MLX 객체를 가리키는 포인터
	void	*win; // mlx_new_window로 만든 창에 대한 포인터 반환
};

// image data 구조체
struct s_data
{
	void	*img; // 이미지 객체를 가리키는 포인터
	char	*addr; // 픽셀을 이미지에 쓰기 위해 이미지의 주소를 가리키는 포인터
	/* 밑의 변수들은 mlx_get_data_addr에 의해 채워진다. */
	int		bits_per_pixel; // 픽셀의 비트 수
	int		line_length; // 픽셀의 한 줄의 바이트 수
	int		endian; // 픽셀의 엔디안
};

#endif
