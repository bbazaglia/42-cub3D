/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:43:33 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 12:00:44 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_format(char *argv)
{
	int	len;

	len = ft_strlen(argv) - 1;
	if (argv[len] != 'b' || argv[len - 1] != 'u' || argv[len - 2] != 'c'
		|| argv[len - 3] != '.')
		exit(printf("Error: The file must be .cub format\n"));
}

static void	check_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			game_over("Invalid character found in map");
		i++;
	}
}

static void	check_boundaries(t_game *game, char *line, int row)
{
	int	i;
	int	len;

	i = 0;
	if (row == 0 || row == (int)game->height - 1)
	{
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' ')
				game_over("Boundaries must be set to 1");
			i++;
		}
	}
	len = ft_strlen(line);
	if ((line[0] != '1' && line[0] != ' ') || (line[len - 1] != '1' \
		&& line[len - 1] != ' '))
		game_over("Boundaries must be set to 1");
}

void	check_data(t_game *game)
{
	t_scene	*scene_data;

	scene_data = game->scene_data;
	if (scene_data->north != 1 || scene_data->south != 1
		|| scene_data->west != 1 || scene_data->east != 1
		|| scene_data->floor != 1 || scene_data->ceiling != 1)
		game_over("Error: Wrong amount of textures");
}

void	validate_map(t_game *game)
{
	int		i;
	size_t	len;

	i = 0;
	while (game->map[i])
	{
		check_boundaries(game, game->map[i], i);
		check_characters(game->map[i]);
		len = ft_strlen(game->map[i]);
		if (len < game->width)
			game->map[i] = fill_spaces(game->map[i], game);
		i++;
	}
}
