#include "cub3d_refactored.h"

// render_map, texture_to_rgb and put_valid_pixel remain the same

// adjusted to the new variables names and struct
void draw_scene(t_raycast *raycast, t_game *game, int r)
{
    int y;
    double texture_x_coord;
    double texture_y_coord;
    double texture_y_step;
    uint32_t color;

    raycast->corrected_angle = game->player->angle - raycast->ray_angle;
    norm_angle(&raycast->corrected_angle);
    raycast->shortest_dist = cos(raycast->corrected_angle) * raycast->shortest_dist;
    raycast->line_height = (HEIGHT * CELL) / raycast->shortest_dist;
    raycast->line_offset = (HEIGHT - raycast->line_height) / 2;
    texture_y_step = game->tex_height / raycast->line_height;
    texture_y_coord = 0;
    if (raycast->is_horizontal)
        texture_x_coord = (int)(raycast->shortest_hit.x * (game->tex_width / CELL)) % game->tex_width;
    else
        texture_x_coord = (int)(raycast->shortest_hit.y * (game->tex_height / CELL)) % game->tex_height;
    y = 0;
    while (y < raycast->line_height)
    {
        color = texture_to_rgb(get_wall(game, raycast), texture_x_coord, texture_y_coord);
        put_valid_pixel(game->player_image, r + 500, raycast->line_offset + y, color);
        texture_y_coord += texture_y_step;
        y++;
    }
}

// just changed the names point_1 and point_2 to start and end
void fill_cell(t_coord *start, t_coord *end, mlx_image_t *mlx_image)
{
    int x;
    int y;
    uint32_t color;

    x = start->x;
    y = start->y;
    color = start->color;
    while (y <= end->y)
    {
        x = start->x;
        while (x <= end->x)
        {
            put_valid_pixel(mlx_image, x, y, color);
            x++;
        }
        y++;
    }
}

// adjusted to the new variables names and struct
mlx_texture_t *get_wall(t_game *game, t_raycast *raycast)
{
    if (raycast->is_horizontal)
    {
        if (raycast->ray_angle > PI && raycast->ray_angle < 2 * PI)
            return (game->no_text);
        else
            return (game->so_text);
    }
    else
    {
        if (raycast->ray_angle < PI / 2 || raycast->ray_angle > 3 * PI / 2)
            return (game->ea_text);
        else
            return (game->we_text);
    }
}
