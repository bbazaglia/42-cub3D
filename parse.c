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

void	parse_file(int argc, char *argv, t_game *game)
{
	int	row;

	if (argc != 2)
		exit(printf("Error: Invalid number of arguments\n"));
	check_format(argv);
	read_scene(game, argv);
	row = check_misconfiguration(game);
	read_map(game, row);
	validate_map(game);
}

void	read_scene(t_game *game, char *argv)
{
	int	fd;
	int	row;
	
	init_data(game);
	get_num_lines(argv, game->scene_data);
	game->scene = malloc(sizeof(char *) * (game->scene_data->size + 1));
	if (game->scene == NULL)
		exit(printf("Error: Memory allocation failed\n"));
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		game_over("Error: Error opening .cub file\n", game);
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

void	read_map(t_game *game, int row)
{
	int i;

	game->height = game->scene_data->size - row;
	game->width = 0;
	game->map = malloc(sizeof(char *) * (game->height + 1));
	i = 0;
	while (game->scene[row])
	{
		game->map[i] = game->scene[row];
		if (is_empty_line(game->map[i]))
			game_over("Error: Empty line in the map\n", game);
		if (ft_strlen(game->map[i]) > game->width)
			game->width = ft_strlen(game->map[i]);
		i++;
		row++;
	}
	game->map[i] = NULL;
	init_player(game, game->map);
	check_data(game);
}

void	get_num_lines(char *argv, t_scene *scene_data)
{
	int		fd;
	char	*line;
	int		num_lines;

	scene_data->size = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(printf("Error: Error opening the map file\n"));
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

