#include "cub3d.h"

void	load_images(t_game *game)
{
    game->no_text = mlx_load_png(game->scene_data->north_path);
    game->so_text = mlx_load_png(game->scene_data->south_path);
    game->we_text = mlx_load_png(game->scene_data->west_path);
    game->ea_text = mlx_load_png(game->scene_data->east_path);
    game->tex_width = game->no_text->width;
    game->tex_height = game->no_text->height;
}

void render_background(t_game *game)
{
    size_t x;
    size_t y;

    x = 500;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            if (y < (HEIGHT / 2))
                mlx_put_pixel(game->mlx_image, x, y, game->scene_data->c_color);
            else
                mlx_put_pixel(game->mlx_image, x, y, game->scene_data->f_color);
            y++;
        }
        x++;
    }
}
