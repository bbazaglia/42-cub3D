/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:37:31 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/19 18:15:21 by string           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void game_over(char *msg)
{
    int exit_code;

    exit_code = EXIT_SUCCESS;
    if (msg)
    {
        printf("%s\n", msg);
        exit_code = EXIT_FAILURE;
    }
    free_mem(get_mem_address()); 
	exit(exit_code);
}

void end_mlx(t_game *game)
{
    delete_images(game);
    // mlx_delete_image(game->mlx, game->mlx_image);
    // mlx_close_window(game->mlx);
	// mlx_terminate(game->mlx);
}

void delete_images(t_game *game)
{
    mlx_delete_texture(game->no_text);
    mlx_delete_texture(game->so_text);
    mlx_delete_texture(game->we_text);
    mlx_delete_texture(game->ea_text);
}