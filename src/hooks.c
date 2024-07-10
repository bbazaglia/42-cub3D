#include "cub3d.h"

void hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		game_over("Game Over\n");
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_vertical(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_vertical(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_horizontal(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_horizontal(game, -1);
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
