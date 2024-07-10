/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:37:31 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/03 15:28:00 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void game_over(char *msg)
{
    char *param;
    int exit_code;

    param = NULL;
    exit_code = EXIT_SUCCESS;
    if (msg)
    {
        printf("%s\n", msg);
        exit_code = EXIT_FAILURE;
    }
    free_mem(get_mem_address()); 
    close_window(param);
	exit(exit_code);
}

void close_window(void *param)
{
    t_game *game;

    game = param;
    delete_images(game);
    mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
}

void delete_images(t_game *game)
{
    mlx_delete_image(game->mlx, game->no_img);    
    mlx_delete_image(game->mlx, game->so_img);
    mlx_delete_image(game->mlx, game->we_img);
    mlx_delete_image(game->mlx, game->ea_img);
    mlx_delete_image(game->mlx, game->background);
    mlx_delete_texture(game->no_text);
    mlx_delete_texture(game->so_text);
    mlx_delete_texture(game->we_text);
    mlx_delete_texture(game->ea_text);
}