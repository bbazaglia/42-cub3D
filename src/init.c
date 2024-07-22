/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:39:35 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 12:01:18 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game, char **map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				game->scene_data->player_count++;
				game->player->map_x_coord = x;
				game->player->map_y_coord = y;
				game->player->facing_dir = map[y][x];
				check_player_path(game, x, y);
			}
			x++;
		}
		y++;
	}
	check_player(game);
}

void	check_player_path(t_game *game, int x, int y)
{
	if (game->map[y + 1][x] == '1' && game->map[y - 1][x] == '1'
		&& game->map[y][x + 1] == '1' && game->map[y][x - 1] == '1')
		game_over("Error: The player is stucked");
}

void	check_player(t_game *game)
{
	char	**map;

	map = game->map;
	if (game->scene_data->player_count != 1)
		game_over("Error: Incorrect number of players in the map");
	if (game->player->map_x_coord != -1 && game->player->map_y_coord != -1)
		map[game->player->map_y_coord][game->player->map_x_coord] = '0';
	else
		game_over("Error: Player's starting position not found");
}

void	init_data(t_game *game)
{
	game->player = allocate_mem(1, sizeof(t_player));
	if (game->player == NULL)
		game_over("Error: Memory allocation failed for player");
	game->scene_data = allocate_mem(1, sizeof(t_scene));
	if (game->scene_data == NULL)
		game_over("Error: Memory allocation failed for scene data");
	game->player->facing_dir = ' ';
	game->player->map_x_coord = -1;
	game->player->map_y_coord = -1;
	game->scene_data->player_count = 0;
	game->scene_data->north = 0;
	game->scene_data->south = 0;
	game->scene_data->west = 0;
	game->scene_data->east = 0;
	game->scene_data->floor = 0;
	game->scene_data->ceiling = 0;
}

void	init_pos(t_game *game)
{
	if (game->player->facing_dir == 'N')
		game->player->angle = PI_270;
	else if (game->player->facing_dir == 'S')
		game->player->angle = PI_90;
	else if (game->player->facing_dir == 'E')
		game->player->angle = 0;
	else if (game->player->facing_dir == 'W')
		game->player->angle = PI;
	game->player->pos.x = (game->player->map_x_coord * CELL) + (CELL / 2);
	game->player->pos.y = (game->player->map_y_coord * CELL) + (CELL / 2);
}
