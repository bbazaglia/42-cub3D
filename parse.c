/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:41:37 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/03 16:05:55 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* to do: PARSING
locate the player's starting position ('N', 'S', 'E', or 'W')
normalize data by replacing it with 0 and store both the coordinates (x, y) of the player's starting position and the direction they are facing
*/

void	validate_input(int argc, char *argv, t_game *game)
{
	if (argc != 2)
		exit(printf("Error: Invalid number of arguments\n"));
	check_format(argv);
	get_num_lines(argv, game->map_data);
	game->player = 0;
	read_map(game, argv);
	if (game->player != 1)
		game_over("Error: Only one player is allowed\n");
}

// read the map data from a file into a two-dimensional character array (char **map)
void	read_map(t_game *game, char *argv)
{
	int	fd;
	int	row;
	int	len;

	game->map = malloc(sizeof(char *) * (game->map_data->size + 1));
	if (game->map == NULL)
		exit(printf("Error: Memory allocation failed\n"));
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		game_over("Error: Error opening the map file\n", game);
	row = 0;
	while (row < game->map_data->size)
	{
		game->map[row] = get_next_line(fd);
		if (game->map[row] == NULL)
			game_over("Error: Failed to read line\n", game);
		check_boundaries(game, game->map[row], row);
		check_characters(game, game->map[row]);
		len = ft_strlen(game->map[row]);
		if (len < game->map_data->max_len)
			game->map[row] = fill_spaces(game->map[row]);
		row++;
	}
	game->map[row] = NULL;
	close(fd);
}

// replace empty spaces with walls
char	*fill_spaces(char *cur_line, t_game *game)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = malloc(sizeof(char) * (game->map_data->max_len + 1));
	if (new_line == NULL)
		game_over("Memory allocation failed\n", game);
	while (cur_line[i])
	{
		new_line[i] = cur_line[i];
		i++;
	}
	while (i < max_len)
	{
		new_line[i] = '1';
		i++;
	}
	new_line[i] = '\0';
	free(cur_line);
	return (new_line);
}

// to-do: what if there's an empty line in the map file?
void	get_num_lines(char *argv, t_map_data *map_data)
{
	int		fd;
	char	*line;
	int		num_lines;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(printf("Error: Error opening the map file\n"));
	map_data->max_len = 0;
	num_lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// find max len of all lines to allocate enough mem for matrix
		if (ft_strlen(line) > map_data->max_len)
			map_data->max_len = ft_strlen(line);
		num_lines++;
		free(line);
	}
	close(fd);
	map_data->size = num_lines;
}
