/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_misconfiguration.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:03:07 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/17 13:05:41 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_path(char *line, int *path_count, char **path)
{
	*path_count = *path_count + 1;
	if (open(line, O_RDONLY) == -1)
		game_over("Error: Invalid texture path\n");
	*path = ft_strdup(line);
}

static char	**get_colors(char *line, int *color_count)
{
	int		i;
	char	**rgb;

	*color_count = *color_count + 1;
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
	return (rgb);
}

static void	check_rgb(char *line, int *color_count, uint32_t *color)
{
	char	**rgb;
	int		i;
	int		j;
	int		valid_color;

	rgb = get_colors(line, color_count);
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

static int	check_line(char **line, t_game *game, t_scene *scene_data, int row)
{
	if (!ft_strncmp(line[0], "NO", 2))
		check_path(line[1], &scene_data->north, &scene_data->north_path);
	else if (!ft_strncmp(line[0], "SO", 2))
		check_path(line[1], &scene_data->south, &scene_data->south_path);
	else if (!ft_strncmp(line[0], "WE", 2))
		check_path(line[1], &scene_data->west, &scene_data->west_path);
	else if (!ft_strncmp(line[0], "EA", 2))
		check_path(line[1], &scene_data->east, &scene_data->east_path);
	else if (!ft_strncmp(line[0], "F", 1))
		check_rgb(game->scene[row], &scene_data->floor, &scene_data->floor_color);
	else if (!ft_strncmp(line[0], "C", 1))
		check_rgb(game->scene[row], &scene_data->ceiling, &scene_data->ceiling_color);
	else
		return (0);
	return (1);
}

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
			if (!check_line(line, game, scene_data, row))
				break ;
		}
		row++;
	}
	check_data(game);
	return (row);
}
