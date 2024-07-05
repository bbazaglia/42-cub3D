/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:41:37 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 18:22:59 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* to do: 
locate the player's starting position ('N', 'S', 'E', or 'W')
normalize scene_data by replacing it with 0 and store both the coordinates (x, y) of the player's starting position and the direction they are facing
*/

void	validate_input(int argc, char *argv, t_game *game)
{
	int	row;

	if (argc != 2)
		exit(printf("Error: Invalid number of arguments\n"));
	check_format(argv);
	game->player = 0;
	read_scene(game, argv);
	while (!game->scene_data->scene_error)
	{
		row = check_misconfiguration(game);
		read_map(game, row);
		validate_map(game);
	}
	if (game->scene_data->scene_error || game->player != 1)
		game_over("Error\n");
}

void	validate_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		check_boundaries(game, game->map[i], i);
		check_characters(game, game->map[i]);
		len = ft_strlen(game->map[i]);
		if (len < game->scene_data->max_len)
			game->map[i] = fill_spaces(game->map[i]);
		i++;
	}
}

void	read_scene(t_game *game, char *argv)
{
	int	fd;
	int	row;

	get_num_lines(argv, game->scene_data);
	game->scene = malloc(sizeof(char *) * (game->scene_data->size + 1));
	if (game->scene == NULL)
		exit(printf("Error: Memory allocation failed\n"));
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		game_over("Error: Error opening the scene file\n", game);
	row = 0;
	while (row < game->scene_data->size)
	{
		game->scene[row] = get_next_line(fd);
		if (game->scene[row] == NULL)
			game_over("Error: Failed to read line\n", game);
		row++;
	}
	game->scene[row] = NULL;
	close(fd);
}

// read the map scene_data from a file into a two-dimensional character array (char **map)
// map can't contain empty lines
void	read_map(t_game *game, int row)
{
	int i;
	int	map_lines;
	int	max_len;

	map_lines = game->scene_data->size - row;
	game->map = malloc(sizeof(char *) * (map_lines + 1));
	max_len = 0;
	i = 0;
	while (scene[row])
	{
		game->map[i] = game->scene[row];
		if (is_empty_line(game->map[i]))
		{
			game->scene_data->scene_error = true;
			break;
		}
		if (ft_strlen(game->map[i]) > game->scene_data->max_len)
			game->scene_data->max_len = ft_strlen(game->map[i]);
		i++;
		row++;
	}
	game->map[i] = NULL;
}

void	get_num_lines(char *argv, t_scene *scene_data)
{
	int		fd;
	char	*line;
	int		num_lines;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(printf("Error: Error opening the map file\n"));
	scene_data->max_len = 0;
	num_lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		num_lines++;
		free(line);
	}
	close(fd);
	scene_data->size = num_lines;
}
