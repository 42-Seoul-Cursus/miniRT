#include "mlx.h"
#include "structures.h"
#include "hook.h"
#include "draw.h"
#include "scene.h"
#include "trace.h"

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka; // 8.4 에서 설명

	// malloc 할당 실패 시, 실습에서는 return NULL로 해두었지만, 적절한 에러 처리가 필요하다.
	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->canvas = make_canvas(WIDTH, HEIGHT);
	scene->camera = make_camera(&scene->canvas, point3(0, 0, 0));
	world = make_object(SPHERE, make_sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
	oadd(&world, make_object(SPHERE, make_sphere(point3(0, -1000, 0), 995), color3(1, 1, 1))); // world 에 구3 추가
	oadd(&world, make_object(SPHERE, make_sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
    scene->world = world;
	scene->world = world;
	lights = make_object(LIGHT, make_light(point3(0, 20, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
	scene->light = lights;
	ka = 0.1; // 8.4 에서 설명
	scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
	return (scene);
}

int	open_window(void)
{
	// mlx
	t_vars		vars;
	t_data		image;

	// mlx_init()은 그래픽 연결을 초기화하고, 연결에 대한 식별자를 반환한다.
	// 그래픽 시스템에 대한 연결 설정, MLX 객체 반환
	vars.mlx = mlx_init();

	// mlx_new_window()는 새로운 창을 생성하고, 창에 대한 식별자를 반환한다.
	// mlx_new_window로 만든 창에 대한 포인터 반환
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "miniRT");

	// mlx_new_image()는 새로운 이미지를 생성하고, 이미지에 대한 식별자를 반환한다.
	// mlx_pixel_put은 굉장히 느린 작업이므로, 이미지 객체를 만들어서 한번에 출력하는 것이 좋다.
	// image로 버퍼링을 하고, mlx_put_image_to_window로 한번에 출력한다고 생각하면 된다.
	image.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);

	// mlx_get_data_addr()는 이미지의 주소를 반환한다.
	// 픽셀을 이미지에 쓰기 위해 이미지의 주소를 가리키는 포인터 반환
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);

	// raytracing

	t_color3	pixel_color;
	t_scene		*scene;

	scene = scene_init();

	for (int i = 0; i < scene->canvas.height; ++i)
	{
		for (int j = 0; j < scene->canvas.width; ++j)
		{
			double v = (double)i / (scene->canvas.width - 1);
			double u = (double)j / (scene->canvas.height - 1);
			//ray from camera origin to pixel
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(&image, j, i, create_trgb(0, pixel_color));
		}
	}

	// mlx_put_image_to_window()는 이미지를 창에 출력한다.
	// 이미지 객체를 창에 출력
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);

	// mlx_hook()은 창에 이벤트가 발생했을 때, 특정 함수를 실행한다.
	// mlx_key_hook은 키보드 이벤트를 처리하는 함수이다. esc key press event
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_hook은 키보드 이벤트를 처리하는 함수이다. close button press event
	mlx_hook(vars.win, 17, 0, exit_hook, 0);
	// mlx_loop는 이벤트를 기다리는 함수이다.
	mlx_loop(vars.mlx);
	return (0);
}
