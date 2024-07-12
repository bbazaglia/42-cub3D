#include "cub3d.h"

bool check_collision(t_game *game, char key)
{
    double x;
    double y;
    size_t mx;
    size_t my;

	if(key == 'w')
	{
		x = game->player->px + game->player->pdx;   
		y = game->player->py + game->player->pdy;
	}
	else if(key == 's')
	{
		x = game->player->px - game->player->pdx;   
		y = game->player->py - game->player->pdy;
	}

    mx = abs((int)(x) >> BIT);
	my = abs((int)(y) >> BIT);

	if (mx < game->width && my < game->height && game->map[my][mx] == '0')
        return (false);
    return (true);
}

void hook(mlx_key_data_t keydata, void *param)
{
	bool collision;
	t_game *game;

	game = param;


	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_terminate(game->mlx);
			// game_over("Game Over\n");
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
			collision = check_collision(game, 'w');

			if(!collision)
			{
				game->player->px += game->player->pdx;
				game->player->py += game->player->pdy;
			}
		}
		if (keydata.key == MLX_KEY_S)
		{
			collision = check_collision(game, 's');

			if(!collision)
			{
				game->player->px -= game->player->pdx;
				game->player->py -= game->player->pdy;
			}
			
		}
	if (game->pmlx_image)
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
