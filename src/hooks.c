/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:39:51 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/17 11:48:46 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_collision(t_game *game, char key)
{
	double	x;
	double	y;
	size_t	mx;
	size_t	my;

	x = 0;
	y = 0;
	mx = 0;
	my = 0;
	if (key == 'w')
	{
		x = game->player->pos.x + game->player->delta.x;
		y = game->player->pos.y + game->player->delta.y;
	}
	else if (key == 's')
	{
		x = game->player->pos.x - game->player->delta.x;
		y = game->player->pos.y - game->player->delta.y;
	}
	mx = abs((int)(x) >> BIT);
	my = abs((int)(y) >> BIT);
	if (mx < game->width && my < game->height && game->map[my][mx] == '0')
		return (false);
	return (true);
}

void	hook(mlx_key_data_t keydata, void *param)
{
	bool	collision;
	t_game	*game;

	game = param;
	collision = true;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			game_over("Game Over");
			end_mlx(game);
		}
		if (keydata.key == MLX_KEY_A)
		{
			game->player->angle -= 0.1;
			if (game->player->angle < 0)
				game->player->angle += 2 * PI;
			game->player->delta.x = cos(game->player->angle) * 5;
			game->player->delta.y = sin(game->player->angle) * 5;
		}
		if (keydata.key == MLX_KEY_D)
		{
			game->player->angle += 0.1;
			if (game->player->angle > 2 * PI)
				game->player->angle -= 2 * PI;
			game->player->delta.x = cos(game->player->angle) * 5;
			game->player->delta.y = sin(game->player->angle) * 5;
		}
		if (keydata.key == MLX_KEY_W)
		{
			collision = check_collision(game, 'w');
			if (!collision)
			{
				game->player->pos.x += game->player->delta.x;
				game->player->pos.y += game->player->delta.y;
			}
		}
		if (keydata.key == MLX_KEY_S)
		{
			collision = check_collision(game, 's');
			if (!collision)
			{
				game->player->pos.x -= game->player->delta.x;
				game->player->pos.y -= game->player->delta.y;
			}
		}
		if (game->player_image)
			mlx_delete_image(game->mlx, game->player_image);
		game->player_image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->player_image, 0, 0);
		get_distance(game);
	}
}

// void	move_vertical(t_game *game, int direction)
// {
// 	game->player->pos.x += game->player->delta.x * 5 * direction;
// 	game->player->pos.y += game->player->delta.y * 5 * direction;
// }

// void	move_horizontal(t_game *game, int direction)
// {
// 	game->player->angle += 5 * direction;
// 	game->player->delta.x = cos(game->player->angle);
// 	game->player->delta.y = -sin(game->player->angle);
// }

