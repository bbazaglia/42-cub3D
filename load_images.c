#include "cub3d.h"

void	load_images(t_game *game)
{
    game->north = mlx_load_png(game->scene_data->north_path);
    game->south = mlx_load_png(game->scene_data->south_path);
    game->west = mlx_load_png(game->scene_data->west_path);
    game->east = mlx_load_png(game->scene_data->east_path);
}

