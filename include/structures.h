#ifndef STRUCTURES_H
# define STRUCTURES_H

# define WIDTH 1440
# define HEIGHT 900

typedef enum e_bool t_bool;
typedef struct s_vec3 t_vec3;
typedef struct s_vec3 t_point3;
typedef struct s_vec3 t_color3;
typedef struct s_ray t_ray;
typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;
typedef struct s_sphere t_sphere;

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
	t_vec3		horizontal; // 수평길이 벡터
	t_vec3		vertical; // 수직길이 벡터
	double		focal_len; // focal length
	t_point3	left_bottom; // 왼쪽 아래 코너점
};

struct  s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
};

struct s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
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
