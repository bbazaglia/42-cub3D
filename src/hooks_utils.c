/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:27:00 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 15:52:32 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_collision(t_game *game, double x, double y)
{
	size_t	mx;
	size_t	my;

	mx = abs((int)(x) >> BIT);
	my = abs((int)(y) >> BIT);
	if (mx < game->width && my < game->height && game->map[my][mx] == '0')
		return (false);
	return (true);
}

void	move_key_w(t_game *game)
{
	double	x;
	double	y;
	bool	collision;

	x = game->player->pos.x + game->player->delta.x;
	y = game->player->pos.y + game->player->delta.y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		game->player->pos.x += game->player->delta.x;
		game->player->pos.y += game->player->delta.y;
	}
}

void	move_key_s(t_game *game)
{
	double	x;
	double	y;
	bool	collision;

	x = game->player->pos.x - game->player->delta.x;
	y = game->player->pos.y - game->player->delta.y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		game->player->pos.x -= game->player->delta.x;
		game->player->pos.y -= game->player->delta.y;
	}
}

void	move_key_a(t_game *game)
{
	double	x;
	double	y;
	bool	collision;
	double	delta_x;
	double	delta_y;

	delta_x = fabs(sin(game->player->angle) * 1);
	delta_y = fabs(cos(game->player->angle) * 1);
	if (game->player->angle > PI)
		x = game->player->pos.x - delta_x;
	else
		x = game->player->pos.x + delta_x;
	if (game->player->angle > PI_90 && game->player->angle < PI_270)
		y = game->player->pos.y + delta_y;
	else
		y = game->player->pos.y - delta_y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		game->player->pos.x = x;
		game->player->pos.y = y;
	}
}

void	move_key_d(t_game *game)
{
	double	x;
	double	y;
	bool	collision;
	double	delta_x;
	double	delta_y;

	delta_x = fabs(sin(game->player->angle) * 1);
	delta_y = fabs(cos(game->player->angle) * 1);
	if (game->player->angle > PI)
		x = game->player->pos.x + delta_x;
	else
		x = game->player->pos.x - delta_x;
	if (game->player->angle > PI_90 && game->player->angle < PI_270)
		y = game->player->pos.y - delta_y;
	else
		y = game->player->pos.y + delta_y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		game->player->pos.x = x;
		game->player->pos.y = y;
	}
}
