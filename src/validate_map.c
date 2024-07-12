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
		check_characters(game->map[i]);
		len = ft_strlen(game->map[i]);
		if (len < game->width)
			game->map[i] = fill_spaces(game->map[i], game);
		i++;
	}
}

void	check_characters(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			game_over("Invalid character found in map\n");
		i++;
	}
}

// check if the map is surrounded by walls ('1')
void	check_boundaries(t_game *game, char *line, int row)
{
	int i;
	int	len;

	i = 0;
	if (row == 0 || row == (int)game->height -1)
	{
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' ')
				game_over("Boundaries must be set to 1\n");
			i++;
		}
	}
	len = ft_strlen(line);
	if ((line[0] != '1' && line[0] != ' ' )|| (line[len - 1] != '1' && line[len - 1] != ' '))
		game_over("Boundaries must be set to 1\n");
}

// replace empty spaces with 1
char	*fill_spaces(char *cur_line, t_game *game)
{
	size_t	i;
	char	*new_line;

	i = 0;
	new_line = allocate_mem(game->width + 1, sizeof(char));
	if (new_line == NULL)
		game_over("Memory allocation failed\n");
	while (cur_line[i])
	{
		if (cur_line[i] == ' ')
			new_line[i] = '1';
		else
			new_line[i] = cur_line[i];
		i++;
	}
	while (i < game->width)
	{
		new_line[i] = '1';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}


