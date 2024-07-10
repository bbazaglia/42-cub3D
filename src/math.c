#include "cub3d.h"

void get_distance(t_game *game)
{
    /* 1. Player - Draw yellow square */

    t_coord point_1;
    t_coord point_2;

	point_1.x = game->player->px - 5;
	point_1.y = game->player->py - 5;
	point_1.color = 0xFFFF00FF;
	point_2.x = game->player->px + 5;
	point_2.y = game->player->py + 5;
	point_2.color = 0xFFFF00FF;

	fill_cell(&point_1, &point_2, game->pmlx_image); 

    /* 2. Player - Draw yellow line direction */

    t_coord point_3;
    t_coord point_4;

	game->player->dirx = (20 * cos(game->player->pa)) + game->player->px;
	game->player->diry = (20 * sin(game->player->pa)) + game->player->py;

	point_3.x = game->player->px;
	point_3.y = game->player->py;
	point_3.color = 0xFFFF00FF;
	point_4.x = game->player->dirx;
	point_4.y = game->player->diry;
	point_4.color = 0xFFFF00FF;

	bresenham(&point_3, &point_4, game->pmlx_image);

    /* Get Distance */
    t_math math;

    math.ra = game->player->pa - (DR * 30);
	if(math.ra < 0)
		math.ra += 2*PI;
	if(math.ra > 2*PI)
		math.ra -= 2*PI;
}

