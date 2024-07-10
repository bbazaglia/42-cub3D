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
    mlx_t		*mlx;
	mlx_image_t	*mlx_image;

    parse_file(argc, argv[1], &game);

    mlx = init_mlx();
    mlx_image = init_image(mlx);

	game.mlx = mlx;
	game.mlx_image = mlx_image;

	render_map(&game); //remove

	init_window(mlx, mlx_image);

    mlx_key_hook(game.mlx, hook, &game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
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
    printf("player position: player[%d][%d]\nplayer dir: %c\n", game.player->mx, game.player->my, game.player->dir);
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
    printf("ceiling color: %u\n", game.scene_data->c_color);
    printf("floor color: %u\n", game.scene_data->f_color);
 
} */
