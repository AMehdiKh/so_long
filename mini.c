#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "/home/amehdikh/MLX42/include/MLX42/MLX42.h"
#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* img;

void	ft_image_to_window(mlx_t *mlx, char *png_path, int x, int y)
{
	mlx_texture_t	*png;

	png = mlx_load_png(png_path);
	if (!png)
	{
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		printf("l7wa");
	}
	if (!mlx_draw_texture(img, png, x * 72, y * 72))
		mlx_delete_texture(png);

	// mlx_delete_texture(png);
}

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

	mlx = mlx_init(600, 600, "MLX42", true);
	img = mlx_new_image(mlx, 600, 600);
	memset(img->pixels, 255, img->width * img->height * sizeof(int));
	mlx_image_to_window(mlx, img, 0, 0);
	ft_image_to_window(mlx, "./textures/space_grass.png", 1, 1);
	ft_image_to_window(mlx, "./textures/eye.png", 1, 1);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
//void mlx_get_monitor_size(int32_t index, int32_t* width, int32_t* height);

//gcc mini.c /Users/ael-khel/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/ael-khel/goinfre/homebrew/opt/glfw/lib"
//gcc mini.c /home/amehdikh/MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm