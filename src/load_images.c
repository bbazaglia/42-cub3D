/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:38:27 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/17 12:11:20 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	safe_load(char *tex_path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(tex_path);
	if (!*texture)
		game_over("Error: loading png");
}

void	load_images(t_game *game)
{
	safe_load(game->scene_data->north_path, &game->no_text);
	safe_load(game->scene_data->south_path, &game->so_text);
	safe_load(game->scene_data->west_path, &game->we_text);
	safe_load(game->scene_data->east_path, &game->ea_text);
	game->tex_width = game->no_text->width;
	game->tex_height = game->no_text->height;
}
