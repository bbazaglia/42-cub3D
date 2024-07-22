/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:02:55 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 09:26:30 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_wall_attributes(t_raycast *raycast, t_game *game)
{
	raycast->corrected_angle = game->player->angle - raycast->ray_angle;
	norm_angle(&raycast->corrected_angle);
	raycast->shortest_dist = cos(raycast->corrected_angle)
		* raycast->shortest_dist;
	raycast->line_height = (HEIGHT * CELL) / raycast->shortest_dist;
	raycast->line_offset = (HEIGHT - raycast->line_height) / 2;
}

static uint32_t	texture_to_rgb(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*rgb;

	rgb = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
}

static mlx_texture_t	*get_wall(t_game *game, t_raycast *raycast)
{
	if (raycast->is_horizontal)
	{
		if (raycast->ray_angle > PI && raycast->ray_angle < PI_360)
			return (game->no_text);
		else
			return (game->so_text);
	}
	else
	{
		if (raycast->ray_angle < PI_90 || raycast->ray_angle > PI_270)
			return (game->ea_text);
		else
			return (game->we_text);
	}
}

void	draw_wall(t_raycast *raycast, t_game *game, int r)
{
	int			y;
	double		texture_x_coord;
	double		texture_y_coord;
	double		texture_y_step;
	uint32_t	color;

	set_wall_attributes(raycast, game);
	texture_y_step = game->tex_height / raycast->line_height;
	texture_y_coord = 0;
	if (raycast->is_horizontal)
		texture_x_coord = (int)(raycast->shortest_hit.x \
		* (game->tex_width / CELL)) % game->tex_width;
	else
		texture_x_coord = (int)(raycast->shortest_hit.y \
		* (game->tex_height / CELL)) % game->tex_height;
	y = 0;
	while (y < raycast->line_height)
	{
		color = texture_to_rgb(get_wall(game, raycast), \
			texture_x_coord, texture_y_coord);
		put_valid_pixel(game->mlx_image, r + 500, raycast->line_offset + y, \
			color);
		texture_y_coord += texture_y_step;
		y++;
	}
}

void	render_background(t_game *game)
{
	size_t	x;
	size_t	y;

	x = 500;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < (HEIGHT / 2))
				put_valid_pixel(game->mlx_image, x, y,
					game->scene_data->ceiling_color);
			else
				put_valid_pixel(game->mlx_image, x, y,
					game->scene_data->floor_color);
			y++;
		}
		x++;
	}
}
