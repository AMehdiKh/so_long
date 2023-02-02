#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "/Users/ael-khel/MLX42/include/MLX42/MLX42.h"
#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* img;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

int32_t	main(void)
{	
	mlx_t* mlx;
	mlx_set_setting(MLX_HEADLESS, true);

	int width;
	int height;

	if (!(mlx = mlx_init(512, 512, "MLX42", false)))
		return(EXIT_FAILURE);
	mlx_get_monitor_size(0, &width, &height);
	img = mlx_new_image(mlx, 128, 128);
	memset(img->pixels, 255, img->width * img->height * sizeof(int));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	printf("\n%d, %d\n", width, height);
	return (EXIT_SUCCESS);
}
//void mlx_get_monitor_size(int32_t index, int32_t* width, int32_t* height);

//gcc mini.c /Users/ael-khel/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/ael-khel/goinfre/homebrew/opt/glfw/lib"