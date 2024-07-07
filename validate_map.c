/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:43:33 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 18:17:55 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_map(t_game *game)
{
	int	i;
	size_t len;

	i = 0;
	while (game->map[i])
	{
		check_boundaries(game, game->map[i], i);
		check_characters(game, game->map[i]);
		len = ft_strlen(game->map[i]);
		if (len < game->width)
			game->map[i] = fill_spaces(game->map[i], game);
		i++;
	}
}

void	check_characters(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			game_over("Invalid character found in map\n", game);
	}
}

// check if the map is surrounded by walls ('1')
void	check_boundaries(t_game *game, char *line, int row)
{
	int	len;

	if (row == 0 || row == game->scene_data->size -1)
	{
		while (line)
		{
			if (*line != '1')
				game_over("Boundaries must be set to 1\n", game);
		}
	}
	len = ft_strlen(line);
	if (line[0] != '1' || line[len] != '1')
		game_over("Boundaries must be set to 1\n", game);
}

// replace empty spaces with spaces
char	*fill_spaces(char *cur_line, t_game *game)
{
	size_t	i;
	char	*new_line;

	i = 0;
	new_line = malloc(sizeof(char) * (game->width + 1));
	if (new_line == NULL)
		game_over("Memory allocation failed\n", game);
	while (cur_line[i])
	{
		new_line[i] = cur_line[i];
		i++;
	}
	while (i < game->width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	free(cur_line);
	return (new_line);
}
