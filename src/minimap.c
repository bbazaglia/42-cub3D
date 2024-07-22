/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:46:23 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 09:21:04 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_square(t_game *game)
{
	t_coord	player_square_start;
	t_coord	player_square_end;

	player_square_start.x = game->player->pos.x - 5;
	player_square_start.y = game->player->pos.y - 5;
	player_square_start.color = 0xFFFF00FF;
	player_square_end.x = game->player->pos.x + 5;
	player_square_end.y = game->player->pos.y + 5;
	player_square_end.color = 0xFFFF00FF;
	fill_cell(&player_square_start, &player_square_end, game->mlx_image);
}

void	draw_player_direction(t_game *game)
{
	t_coord	player_center_pos;
	t_coord	direction;

	game->player->dir_vector.x = (20 * cos(game->player->angle))
		+ game->player->pos.x;
	game->player->dir_vector.y = (20 * sin(game->player->angle))
		+ game->player->pos.y;
	player_center_pos.x = game->player->pos.x;
	player_center_pos.y = game->player->pos.y;
	player_center_pos.color = 0xFFFF00FF;
	direction.x = game->player->dir_vector.x;
	direction.y = game->player->dir_vector.y;
	direction.color = 0xFFFF00FF;
	bresenham(&player_center_pos, &direction, game->mlx_image);
}

void	print_ray(t_game *game, t_raycast *raycast)
{
	t_coord	ray_start;
	t_coord	ray_end;

	ray_start.x = game->player->pos.x;
	ray_start.y = game->player->pos.y;
	ray_start.color = 0xFF0000FF;
	ray_end.x = raycast->shortest_hit.x;
	ray_end.y = raycast->shortest_hit.y;
	ray_end.color = 0xFF0000FF;
	bresenham(&ray_start, &ray_end, game->mlx_image);
}

static void	color_minimap(t_coord *start, t_coord *end, char map, t_game *game)
{
	if (map == '1')
	{
		start->color = 0xffffffff;
		end->color = 0xffffffff;
	}
	else
	{
		start->color = 0x00000000;
		end->color = 0x00000000;
	}
	fill_cell(start, end, game->mlx_image);
}

void	render_minimap(t_game *game)
{
	size_t	i;
	size_t	j;
	t_coord	start;
	t_coord	end;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			start.x = CELL * j;
			start.y = CELL * i;
			end.x = (CELL * j) + (CELL - 1);
			end.y = (CELL * i) + (CELL - 1);
			color_minimap(&start, &end, game->map[i][j], game);
			j++;
		}
		i++;
	}
}
