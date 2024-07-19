/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:39:51 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/19 17:18:47 by string           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hook(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			close_window(game);
		if (keydata.key == MLX_KEY_LEFT)
			rotate_key_left(game);
		if (keydata.key == MLX_KEY_RIGHT)
			rotate_key_right(game);
		if (keydata.key == MLX_KEY_W)
			move_key_w(game);
		if (keydata.key == MLX_KEY_S)
			move_key_s(game);
		if (keydata.key == MLX_KEY_A)
			move_key_a(game);
		if (keydata.key == MLX_KEY_D)
			move_key_d(game);
		if (game->player_image)
			mlx_delete_image(game->mlx, game->player_image);
		game->player_image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->player_image, 0, 0);
		get_distance(game);
	}
}

void close_window(t_game *game)
{
	game_over("Game Over");
	end_mlx(game);
}

void rotate_key_left(t_game *game)
{
	game->player->angle -= 0.1;
	if (game->player->angle < 0)
		game->player->angle += PI_360;
	game->player->delta.x = cos(game->player->angle) * 5;
	game->player->delta.y = sin(game->player->angle) * 5;
}

void rotate_key_right(t_game *game)
{
	game->player->angle += 0.1;
	if (game->player->angle > PI_360)
		game->player->angle -= PI_360;
	game->player->delta.x = cos(game->player->angle) * 5;
	game->player->delta.y = sin(game->player->angle) * 5;
}

