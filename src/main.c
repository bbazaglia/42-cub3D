/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/19 13:59:56 by string           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game		game;

	parse_file(argc, argv[1], &game);
    safe_mlx_action(INIT, &game);
    safe_mlx_action(NEW_IMAGE, &game);
	game.player_image = NULL;
	load_images(&game);
	render_minimap(&game); //remove
    safe_mlx_action(IMAGE_TO_WINDOW, &game);
	mlx_key_hook(game.mlx, hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

/* int main(int argc, char **argv)
{
    t_game game;

    parse_file(argc, argv[1], &game);
    // game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
    // if (!game.mlx)
    //     game_over("Error: Failed to initialize mlx\n");
    // mlx_key_hook(game.mlx, hook, &game);



    print statements
    printf("GAME SCENE\n");
    int i = 0;
    while (game.scene[i])
    {
        printf("%s\n", game.scene[i]);
        i++;
    }
    printf("\nGAME MAP\n");
    i = 0;
    while (game.map[i])
    {
        printf("%s\n", game.map[i]);
        i++;
    }
    printf("\nGAME DATA SCENE\n");
    printf("player position: player[%d][%d]\nplayer dir: %c\n", game.player->mx,
		game.player->my, game.player->dir);
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
    printf("ceiling color: %u\n", game.scene_data->ceiling_color);
    printf("floor color: %u\n", game.scene_data->floor_color);
 
} */
