#include "cub3d.h"

void init_player(t_game *game, char **map)
{
    size_t x;
    size_t y;

    x = 0;
    y = 0;
    while (y < game->height)
    {
        x = 0;
        while (x < game->width)
        {
            // count players and locate player's starting position
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
            {
                game->scene_data->player_count++;
                game->player->mx = x;
                game->player->my = y;
                game->player->dir = map[y][x];
            }
            x++;
        }
        y++;
    }
}

void init_data(t_game *game)
{
    game->player = allocate_mem(1, sizeof(t_player));
    if (game->player == NULL)
        game_over("Error: Memory allocation failed for player\n");
    game->scene_data = allocate_mem(1, sizeof(t_scene));
    if (game->scene_data == NULL)
        game_over("Error: Memory allocation failed for scene data\n");
    game->player->dir = ' ';
    game->player->mx = -1;
    game->player->my = -1;
    game->scene_data->player_count = 0;
    game->scene_data->north = 0;
    game->scene_data->south = 0;
    game->scene_data->west = 0;
    game->scene_data->east = 0;
    game->scene_data->floor = 0;
    game->scene_data->ceiling = 0;
}

void init_pos(t_game *game)
{
    if (game->player->dir == 'N')
        game->player->pa = 3*PI / 2;
    else if (game->player->dir == 'S')
        game->player->pa = PI / 2;
    else if (game->player->dir == 'E')
        game->player->pa = 0;
    else if (game->player->dir == 'W')
        game->player->pa = PI;

    game->player->px = (game->player->mx * CELL) + (CELL / 2);
    game->player->py = (game->player->my * CELL) + (CELL / 2);
}

mlx_t	*init_mlx(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!mlx)
		game_over("Error: mlx"); 
	return (mlx);
}

mlx_image_t	*init_image(mlx_t *mlx)
{
	mlx_image_t	*mlx_image;

	mlx_image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!mlx_image)
		game_over("Error: mlx"); 
	return (mlx_image);
}

void	init_window(mlx_t *mlx, mlx_image_t *mlx_image)
{
	if (mlx_image_to_window(mlx, mlx_image, 0, 0) == -1)
	    game_over("Error: mlx"); 
}
