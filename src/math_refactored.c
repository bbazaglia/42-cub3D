#include "cub3d_refactored.h"

/*-------------------GET DISTANCE FUNCTION REFACTORED------------------------
functions added:
    - draw_player_square
    - draw_player_direction
    - find_shortest_distance
    - print_ray
    - calculate_and_update_raycast
    - initialize_raycast
function modified:
    - get_distance
---------------------------------------------------------------------------*/

void draw_player_square(t_game *game)
{
    t_coord player_square_start;
    t_coord player_square_end;

    player_square_start.x = game->player->pos.x - 5;
    player_square_start.y = game->player->pos.y - 5;
    player_square_start.color = 0xFFFF00FF;
    player_square_end.x = game->player->pos.x + 5;
    player_square_end.y = game->player->pos.y + 5;
    player_square_end.color = 0xFFFF00FF;

    fill_cell(&player_square_start, &player_square_end, game->player_image);
}

void draw_player_direction(t_game *game)
{
    t_coord player_center_pos;
    t_coord direction;

    game->player->dir_vector.x = (20 * cos(game->player->angle)) + game->player->pos.x;
    game->player->dir_vector.y = (20 * sin(game->player->angle)) + game->player->pos.y;

    player_center_pos.x = game->player->pos.x;
    player_center_pos.y = game->player->pos.y;
    player_center_pos.color = 0xFFFF00FF;
    direction.x = game->player->dir_vector.x;
    direction.y = game->player->dir_vector.y;
    direction.color = 0xFFFF00FF;

    bresenham(&player_center_pos, &direction, game->player_image);
}

void find_shortest_distance(t_raycast *raycast)
{
    raycast->shortest_hit.x = raycast->vert_hit.x;
    raycast->shortest_hit.y = raycast->vert_hit.y;
    raycast->shortest_dist = raycast->vert_dist;
    raycast->is_horizontal = false;

    if (raycast->horiz_dist < raycast->vert_dist)
    {
        raycast->shortest_hit.x = raycast->horiz_hit.x;
        raycast->shortest_hit.y = raycast->horiz_hit.y;
        raycast->shortest_dist = raycast->horiz_dist;
        raycast->is_horizontal = true;
    }
}

void print_ray(t_game *game, t_raycast *raycast)
{
    t_coord ray_start;
    t_coord ray_end;

    ray_start.x = game->player->pos.x;
    ray_start.y = game->player->pos.y;
    ray_start.color = 0xFF0000FF;
    ray_end.x = raycast->shortest_hit.x;
    ray_end.y = raycast->shortest_hit.y;
    ray_end.color = 0xFF0000FF;

    bresenham(&ray_start, &ray_end, game->player_image);
}

void get_distance(t_game *game)
{
    t_raycast raycast;
    int ray;

    draw_player_square(game);
    draw_player_direction(game);
    render_background(game);
    raycast.ray_angle = game->player->angle - (DR * 30);
    norm_angle(&raycast.ray_angle);
    ray = 0;
    while (ray < 400)
    {
        initialize_raycast(&raycast);
        calculate_and_update_raycast(&raycast, game, ray);
        ray++;
    }
}

void calculate_and_update_raycast(t_raycast *raycast, t_game *game, int ray)
{
    raycast->tan = (-1) / tan(raycast->ray_angle);
    find_horiz_ray_dim(&raycast, game);
    find_horiz_ray_limit(&raycast, game);
    raycast->rev_tan = (-1) * tan(raycast->ray_angle);
    find_vert_ray_dim(&raycast, game);
    find_vert_ray_limit(&raycast, game);
    find_shortest_distance(&raycast);
    print_ray(game, &raycast);
    draw_scene(&raycast, game, ray);
    raycast->ray_angle += (0.15 * DR);
    norm_angle(&raycast->ray_angle);
}

void initialize_raycast(t_raycast *raycast)
{
    raycast->ray_pos.x = 0;
    raycast->ray_pos.y = 0;
    raycast->horiz_hit.x = 0;
    raycast->horiz_hit.y = 0;
    raycast->horiz_dist = HIGH_VALUE;
    raycast->map_x = 0;
    raycast->map_y = 0;
}

/*-------------------NORM AND DIST FUNCTIONS ARE THE SAME--------------------*/

void norm_angle(double *angle)
{
	if (*angle < 0)
		*angle += (2 * PI);
	if (*angle > (2 * PI))
		*angle -= (2 * PI);
}

double dist(int ax, int ay, int bx, int by)
{
	double result;

	result = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	if(isnan(result))
		result = HIGH_VALUE;
	return (result);
}


/*-------------------FIND RAY DIMENSION AND LIMIT--------------------*/


void find_horiz_ray_dim(t_raycast *raycast, t_game *game)
{
    if (raycast->ray_angle == 0 || raycast->ray_angle == PI)
    {
        raycast->ray_pos.x = game->player->pos.x + game->width;
        raycast->ray_pos.y = game->player->pos.y + game->height;
    }
    else if (raycast->ray_angle > PI) // looking up
    {
        raycast->ray_pos.y = (((int)game->player->pos.y >> BIT) << BIT) - 0.0001;
        raycast->ray_pos.x = (game->player->pos.y - raycast->ray_pos.y) * raycast->tan + game->player->pos.x;
        raycast->step.y = -CELL;
        raycast->step.x = (-raycast->step.y) * raycast->tan;
    }
    else if (raycast->ray_angle < PI) // looking down
    {
        raycast->ray_pos.y = (((int)game->player->pos.y >> BIT) << BIT) + CELL;
        raycast->ray_pos.x = (game->player->pos.y - raycast->ray_pos.y) * raycast->tan + game->player->pos.x;
        raycast->step.y = CELL;
        raycast->step.x = (-raycast->step.y) * raycast->tan;
    }
}

void find_vert_ray_dim(t_raycast *raycast, t_game *game)
{
    if (raycast->ray_angle == PI / 2 || raycast->ray_angle == 3 * PI / 2)
    {
        raycast->ray_pos.x = game->player->pos.x + game->width;
        raycast->ray_pos.y = game->player->pos.y + game->height;
    }
    else if (raycast->ray_angle > PI / 2 && raycast->ray_angle < 3 * PI / 2) // looking left
    {
        raycast->ray_pos.x = (((int)game->player->pos.x >> BIT) << BIT) - 0.0001;
        raycast->ray_pos.y = (game->player->pos.x - raycast->ray_pos.x) * raycast->rev_tan + game->player->pos.y;
        raycast->step.x = -CELL;
        raycast->step.y = (-raycast->step.x) * raycast->rev_tan;
    }
    else if (raycast->ray_angle < PI / 2 || raycast->ray_angle > 3 * PI / 2) // looking right
    {
        raycast->ray_pos.x = (((int)game->player->pos.x >> BIT) << BIT) + CELL;
        raycast->ray_pos.y = (game->player->pos.x - raycast->ray_pos.x) * raycast->rev_tan + game->player->pos.y;
        raycast->step.x = CELL;
        raycast->step.y = (-raycast->step.x) * raycast->rev_tan;
    }
}

void find_horiz_ray_limit(t_raycast *raycast, t_game *game)
{
    raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
    raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);

    while (raycast->map_x < game->width && raycast->map_y < game->height && game->map[raycast->map_y][raycast->map_x] == '0')
    {
        raycast->ray_pos.x += raycast->step.x;
        raycast->ray_pos.y += raycast->step.y;
        raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
        raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);
    }
    raycast->horiz_hit.x = raycast->ray_pos.x;
    raycast->horiz_hit.y = raycast->ray_pos.y;
    raycast->horiz_dist = dist(game->player->pos.x, game->player->pos.y, raycast->horiz_hit.x, raycast->horiz_hit.y);
}

void find_vert_ray_limit(t_raycast *raycast, t_game *game)
{
    raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
    raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);

    while (raycast->map_x < game->width && raycast->map_y < game->height && game->map[raycast->map_y][raycast->map_x] == '0')
    {
        raycast->ray_pos.x += raycast->step.x;
        raycast->ray_pos.y += raycast->step.y;
        raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
        raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);
    }
    raycast->vert_hit.x = raycast->ray_pos.x;
    raycast->vert_hit.y = raycast->ray_pos.y;
    raycast->vert_dist = dist(game->player->pos.x, game->player->pos.y, raycast->vert_hit.x, raycast->vert_hit.y);
}

