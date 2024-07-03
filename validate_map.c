/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:03:07 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/03 16:06:50 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* to do: MAP VALIDATION
elements must come before the map
something is missing (NO, SO, WE, EA, F, C)
something is duplicated 
resolution with int larger than int max
resolution with a comma or other character in it
resolution with 3 digits, or just one, or a 0
F or C with a missing digit, or an extra digit
F or C with one more than 2 commas
F or C with an int greater than int max
F or C with a number greater than 255
a wrong identifier (X instead of R, or E instead of EA)
elements must be configured as: type identifier + path 
check if the path is valid
*/

void	check_format(char *argv)
{
	int	size;

	size = ft_strlen(argv) - 1;
	if (argv[size] != 'b' || argv[size - 1] != 'u' || argv[size - 2] != 'c'
		|| argv[size - 3] != '.')
		exit(printf("Error: The file must be .cub format\n"));
}

void	check_characters(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			game_over("Invalid character found in map\n", game);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			game->player++;
	}
}

// check if the map is surrounded by walls ('1')
void	check_boundaries(t_game *game, char *line, int row)
{
	int	len;

	if (row == 0 || row == game->map_data->size)
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
