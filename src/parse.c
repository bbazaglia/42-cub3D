/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:41:37 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/23 11:15:51 by bbazagli         ###   ########.fr       */
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
	init_player(game, game->map);
	check_data(game);
	init_pos(game);
}

void	read_scene(t_game *game, char *argv)
{
	int	fd;
	int	row;
	int	len;

	init_data(game);
	get_num_lines(argv, game->scene_data);
	game->scene = allocate_mem(game->scene_data->size + 1, sizeof(char *));
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		game_over("Error: Error opening .cub file");
	row = 0;
	while (row < game->scene_data->size)
	{
		game->scene[row] = get_next_line(fd);
		collect_mem(game->scene[row]);
		if (game->scene[row] == NULL)
			game_over("Error: Failed to read line");
		len = ft_strlen(game->scene[row]);
		if (len > 0 && game->scene[row][len - 1] == '\n')
			game->scene[row][len - 1] = '\0';
		row++;
	}
	game->scene[row] = NULL;
	close(fd);
}

void	read_map(t_game *game, int row)
{
	int	i;

	game->height = game->scene_data->size - row;
	game->width = 0;
	game->map = allocate_mem(game->height + 1, sizeof(char *));
	i = 0;
	while (game->scene[row])
	{
		game->map[i] = game->scene[row];
		if (is_empty_line(game->map[i]))
			game_over("Error: Empty line in the map");
		if (ft_strlen(game->map[i]) > game->width)
			game->width = ft_strlen(game->map[i]);
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

	scene_data->size = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		game_over("Error: Error opening the map file");
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
	if (scene_data->size == 0)
		game_over("Error: The file is empty");
}

char	*fill_spaces(char *cur_line, t_game *game)
{
	size_t	i;
	char	*new_line;

	i = 0;
	new_line = allocate_mem(game->width + 1, sizeof(char));
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
