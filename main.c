/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 10:33:48 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    parse_file(argc, argv[1], &game);
    // game.mlx = mlx_init(game.width * PIXELS, game.height * PIXELS,"cub3d", true);
    int i = 0;
    while (game.scene[i])
    {
        printf("%s\n", game.map[i]);
        i++;
    }
    i = 0;
    while (game.map[i])
    {
        printf("%s\n", game.map[i]);
        i++;
    }
    printf("player position: player[%d][%d]\nplayer dir: %c\n", game.player->x, game.player->y, game.player->dir);
    printf("print scene_data info\n");
    printf("size: %d\n", game.scene_data->size);
    printf("player_count: %d\n", game.scene_data->player_count);
    printf("north: %d\n", game.scene_data->north);
    printf("south: %d\n", game.scene_data->south);
    printf("west: %d\n", game.scene_data->west);
    printf("east: %d\n", game.scene_data->east);
    printf("floor: %d\n", game.scene_data->floor);
    printf("ceiling: %d\n", game.scene_data->ceiling);
    printf("north path: %s\n", game.scene_data->north_path);
    printf("south path: %s\n", game.scene_data->south_path);
    printf("west path: %s\n", game.scene_data->west_path);
    printf("east path: %s\n", game.scene_data->east_path);
    printf("ceiling color: %d\n", game.scene_data->c_color);
    printf("floor color: %d\n", game.scene_data->f_color);
}
