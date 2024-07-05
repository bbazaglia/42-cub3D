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

/* check if:
	- something is missing (NO, SO, WE, EA, F, C)
	- something is duplicated 
	- path is valid
	- elements must come before the map
*/
int	check_misconfiguration(t_game *game)
{
	int		row;
	char	**scene;
	char	**line;

	row = 0;
	scene = game->scene;
	init_cardinals(game->scene_data);
	while (scene)
	{
		if (!is_empty_line(scene[row]))
		{
			line = ft_split_space(scene[row]);
			if (!ft_strncmp(line[0], "NO", 2))
				check_path(line[1], &scene_data->north);
			else if (!ft_strncmp(line[0], "SO", 2))
				check_path(line[1], &scene_data->south);
			else if (!ft_strncmp(line[0], "WE", 2))
				check_path(line[1], &scene_data->west);
			else if (!ft_strncmp(line[0], "EA", 2))
				check_path(line[1], &scene_data->east);
			else if (!ft_strncmp(line[0], "F", 1))
				check_rgb(scene[row], &scene_data->floor);
			else if (!ft_strncmp(line[0], "C", 1))
				check_rgb(scene[row], &scene_data->ceiling);
			else
				break ;
		}
		row++;
	}
	check_cardinal(game->scene_data);
	return (row);
}

/* 
rgb contains digits only
rgb contains three digits 
rgb goes from 0 to 255
*/
void	check_rgb(t_scene *scene_data, char *line, int *cardinal)
{
	char	**rgb;
	int		i;
	int		valid_color;
	int32_t	color;

	*cardinal = *cardinal + 1;
	rgb = ft_split(line, ',');
	i = 0;
	while (rgb[i])
	{
		ft_strtrim(rgb[i], " \b\t\n\v\f\r");
		i++;
	}
	if (i > 3)
		scene_data->scene_error = true;
	i = 0;
	while (rgb[i])
	{
		if (!ft_isdigit(rgb[i]))
			scene_data->scene_error = true;
		valid_color = ft_atoi(rgb[i]);
		if (valid_color < 0 || valid_color > 255)
			scene_data->scene_error = true;
	}
	color = ft_pixel(ft_atoi(rbg[0]), ft_atoi(rbg[1]), ft_atoi(rbg[2]), 255);
}

void	check_cardinal(t_scene *scene_data)
{
	if (scene_data->north != 1 || scene_data->south != 1
		|| scene_data->west != 1 || scene_data->east != 1
		|| scene_data->floor != 1 || scene_data->ceiling != 1)
		scene_data->scene_error = true;
}

void	check_path(char *line, int *cardinal)
{
	int	fd;

	*cardinal = *cardinal + 1;
	fd = (open(line) == -1)
		scene_error = true;
}

void	init_cardinals(t_scene *scene_data)
{
	scene_data->north = 0;
	scene_data->south = 0;
	scene_data->west = 0;
	scene_data->east = 0;
	scene_data->floor = 0;
	scene_data->ceiling = 0;
	scene_data->scene_error = false;
}

