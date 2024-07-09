#include "cub3d.h"

void	load_images(t_game *game)
{
    game->no_text = mlx_load_png(game->scene_data->north_path);
    game->so_text = mlx_load_png(game->scene_data->south_path);
    game->we_text = mlx_load_png(game->scene_data->west_path);
    game->ea_text = mlx_load_png(game->scene_data->east_path);
    game->no_img = mlx_texture_to_image(game->mlx, game->no_text);
    game->so_img = mlx_texture_to_image(game->mlx, game->so_text);
    game->we_img = mlx_texture_to_image(game->mlx, game->we_text);
    game->ea_img = mlx_texture_to_image(game->mlx, game->ea_text);
}

void render_background(t_game *game)
{
    size_t x;
    size_t y;

    x = 0;
    game->background = mlx_new_image(game->mlx, game->width * CELL, game->height * CELL);
    if (!game->background)
        game_over("Error: Failed to create background image\n");
    // complete all rows from top to bottom
    while (x < game->height * CELL)
    {
        y = 0;
        // complete all columns from left to right
        while (y < game->width * CELL)
        {
            // if the row is on the top half of the screen, color it with the ceiling color
            if (x < (game->height / 2))
                mlx_put_pixel(game->background, y, x, game->scene_data->c_color);
            // if the row is on the bottom half of the screen, color it with the floor color
            else
                mlx_put_pixel(game->background, y, x, game->scene_data->f_color);
            y++;
        }
        x++;
    }
}
