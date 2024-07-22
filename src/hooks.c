/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:39:51 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 16:58:22 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_key_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_key_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_key_w(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_key_s(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_key_a(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_key_d(game);
	mlx_delete_image(game->mlx, game->mlx_image);
	game->mlx_image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->mlx_image, 0, 0);
	get_distance(game);
}

void	close_window(t_game *game)
{
	end_mlx(game);
	game_over("Game Over");
}

void	rotate_key_left(t_game *game)
{
	game->player->angle -= 0.05;
	if (game->player->angle < 0)
		game->player->angle += PI_360;
	game->player->delta.x = cos(game->player->angle) * 1;
	game->player->delta.y = sin(game->player->angle) * 1;
}

void	rotate_key_right(t_game *game)
{
	game->player->angle += 0.05;
	if (game->player->angle > PI_360)
		game->player->angle -= PI_360;
	game->player->delta.x = cos(game->player->angle) * 1;
	game->player->delta.y = sin(game->player->angle) * 1;
}
