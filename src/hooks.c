#include "cub3d.h"

void	hook(mlx_key_data_t keydata, void *param)
{
    t_game		*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			game_over("Game Over\n");
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
            // add func
		if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			// add func
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			// add func
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			// add func
	}
    // func to update the player's position
}
