/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:03:07 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 18:06:16 by bbazagli         ###   ########.fr       */
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

/* check if:
	- something is missing (NO, SO, WE, EA, F, C)
	- something is duplicated 
	- path is valid
	- elements must come before the map
*/
int	check_misconfiguration(t_game *game)
{
	int		row;
	char	**line;
	t_scene	*scene_data;

	row = 0;
	scene_data = game->scene_data;
	while (game->scene)
	{
		if (!is_empty_line(game->scene[row]))
		{
			line = ft_split_space(game->scene[row]);
			if (!ft_strncmp(line[0], "NO", 2))
				check_path(line[1], &scene_data->north, &scene_data->north_path);
			else if (!ft_strncmp(line[0], "SO", 2))
				check_path(line[1], &scene_data->south, &scene_data->south_path);
			else if (!ft_strncmp(line[0], "WE", 2))
				check_path(line[1], &scene_data->west, &scene_data->west_path);
			else if (!ft_strncmp(line[0], "EA", 2))
				check_path(line[1], &scene_data->east, &scene_data->east_path);
			else if (!ft_strncmp(line[0], "F", 1))
				check_rgb(game->scene[row], &scene_data->floor, &scene_data->f_color);
			else if (!ft_strncmp(line[0], "C", 1))
				check_rgb(game->scene[row], &scene_data->ceiling, &scene_data->c_color);
			else
				break ;
		}
		row++;
	}
	return (row);
}

void	check_path(char *line, int *cardinal, char **path)
{
	*cardinal = *cardinal + 1;
	if (open(line, O_RDONLY) == -1)
		game_over("Error: Invalid texture path\n");
	*path = ft_strdup(line);
}

/* 
rgb contains digits only
rgb contains three digits 
rgb goes from 0 to 255
*/
void	check_rgb(char *line, int *cardinal, uint32_t *color)
{
	char	**rgb;
	int		i;
	int		j;
	int		valid_color;

	*cardinal = *cardinal + 1;
	while (ft_isspace(*line) || *line == 'F' || *line == 'C')
		line++;
	rgb = ft_split(line, ',');
	i = 0;
	while (rgb[i])
	{
		rgb[i] = ft_strtrim(rgb[i], " \b\t\n\v\f\r");
		i++;
	}
	if (i > 3)
		game_over("Error: Invalid color texture\n");
	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
			{
				printf("rgb[i][j]: %d\n", rgb[i][j]);
				game_over("Error: Invalid color texture\n");
			}
			j++;
		}
		valid_color = ft_atoi(rgb[i]);
		if (valid_color < 0 || valid_color > 255)
			game_over("Error: Invalid color texture\n");
		i++;
	}
	*color = ft_pixel(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
}

void	check_data(t_game *game)
{
	char **map;
	t_scene *scene_data;

	map = game->map;
	scene_data = game->scene_data;
	if (scene_data->north != 1 || scene_data->south != 1
		|| scene_data->west != 1 || scene_data->east != 1
		|| scene_data->floor != 1 || scene_data->ceiling != 1)
		game_over("Error: Wrong amount of textures\n");
	if (game->scene_data->player_count != 1)
        game_over("Error: Incorrect number of players in the map\n");
    if (game->player->mx  != -1 && game->player->my != -1)
        map[game->player->my][game->player->mx] = '0'; // normalize map data: replace player's position with 0
    else
        game_over("Error: Player's starting position not found\n");
}
