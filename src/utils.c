/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:47:14 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/19 12:38:00 by string           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	put_valid_pixel(mlx_image_t *mlx_image, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(mlx_image, x, y, color);
}

void	fill_cell(t_coord *start, t_coord *end, mlx_image_t *mlx_image)
{
	int			x;
	int			y;
	uint32_t	color;

	x = start->x;
	y = start->y;
	color = start->color;
	while (y <= end->y)
	{
		x = start->x;
		while (x <= end->x)
		{
			put_valid_pixel(mlx_image, x, y, color);
			x++;
		}
		y++;
	}
}

void	safe_mlx_action(int action, t_game *game)
{
	if (action == INIT)
	{
		game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
		if (!game->mlx)
			game_over("Error: mlx");
	}
	else if (action == NEW_IMAGE)
	{
		game->mlx_image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		if (!game->mlx_image)
			game_over("Error: mlx");
	}
	else if (action == IMAGE_TO_WINDOW)
	{
		if (mlx_image_to_window(game->mlx, game->mlx_image, 0, 0) == -1)
			game_over("Error: mlx");
	}
}
