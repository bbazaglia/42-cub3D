#include "cub3d.h"

void hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			game_over("Game Over\n");
		if (keydata.key == MLX_KEY_A)
		{
			game->player->pa -= 0.1;
			if(game->player->pa < 0)
				game->player->pa += 2*PI;
			game->player->pdx = cos(game->player->pa) * 5;
			game->player->pdy = sin(game->player->pa) * 5;
		}
		if (keydata.key == MLX_KEY_D)
		{
			game->player->pa += 0.1;
			if(game->player->pa > 2*PI)
				game->player->pa -= 2*PI;
			game->player->pdx = cos(game->player->pa) * 5;
			game->player->pdy = sin(game->player->pa) * 5;
		}
		if (keydata.key == MLX_KEY_W)
		{
			game->player->px += game->player->pdx;
			game->player->py += game->player->pdy;
		}
		if (keydata.key == MLX_KEY_S)
		{
			game->player->px -= game->player->pdx;
			game->player->py -= game->player->pdy;
		}

	mlx_delete_image(game->mlx, game->pmlx_image);
	game->pmlx_image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->pmlx_image, 0, 0);
	get_distance(game);
}

	
}

void move_vertical(t_game *game, int direction)
{
	game->player->px += game->player->pdx * 5 * direction;
	game->player->py += game->player->pdy * 5 * direction;
}

void move_horizontal(t_game *game, int direction)
{
	game->player->pa += 5 * direction;
	game->player->pa = fix_ang(game->player->pa);
	game->player->pdx = cos(game->player->pa);
	game->player->pdy = -sin(game->player->pa);
}

double fix_ang(double a)
{
	if (a > 2 * PI)
		a -= 2 * PI;
	if (a < 0)
		a += 2 * PI;
	return (a);
}
