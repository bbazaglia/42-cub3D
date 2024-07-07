#include "cub3d.h"

void    init_player(t_game *game, char **map)
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
                game->player->x = x;
                game->player->y = y;
                game->player->dir = map[y][x];
            }
            x++;
        }
        y++;
    }
}

void init_data(t_game *game)
{
    game->player = malloc(sizeof(t_player));
    if (game->player == NULL)
        exit(printf("Error: Memory allocation failed for player\n"));
    game->scene_data = malloc(sizeof(t_scene));
    if (game->scene_data == NULL)
        exit(printf("Error: Memory allocation failed for scene data\n"));
    game->player->dir = ' ';     
    game->player->x = -1;
    game->player->y = -1;
    game->scene_data->player_count = 0;
    game->scene_data->north = 0;
    game->scene_data->south = 0;
    game->scene_data->west = 0;
    game->scene_data->east = 0;
    game->scene_data->floor = 0;
    game->scene_data->ceiling = 0;
}
