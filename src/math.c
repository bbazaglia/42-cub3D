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
	
	render_background(game);

	/* Get Distance */

	int r;
	t_math math;

	math.ra = game->player->pa - (DR * 30);
	norm_angle(&math.ra);

	r = 0;
	while (r < 400)
	{

		/* HORIZONTAL LINES */

		math.aTan = (-1) / tan(math.ra);
		math.rx = 0;
		math.ry = 0;
		math.hx = 0;
		math.hy = 0;
		math.dist_horiz = HIGH_VALUE;
		math.mx = 0;
		math.my = 0;

		// if(math->ra != 0 && math->ra != PI)
		find_horiz_ray_dim(&math, game);
		find_horiz_ray_limit(&math, game);

		/* VERTICAL LINES */

		math.nTan = (-1) * tan(math.ra);
		math.rx = 0;
		math.ry = 0;
		math.vx = 0;
		math.vy = 0;
		math.dist_vert = HIGH_VALUE;
		math.mx = 0;
		math.my = 0;

		find_vert_ray_dim(&math, game);
		find_vert_ray_limit(&math, game);

		/* find_shortest_distance */
			math.sx = math.vx;
			math.sy = math.vy;
			math.distS = math.dist_vert;
			math.is_horiz = false;

		if (math.dist_horiz < math.dist_vert)
		{
			math.sx = math.hx;
			math.sy = math.hy;
			math.distS = math.dist_horiz;
			math.is_horiz = true;
		}

		if(math.sx > 600)
		{
			printf("dist_horiz: %f, dist_vert: %f\n", math.dist_horiz, math.dist_vert);

			printf("mx: %zu, my: %zu, mp: %c, angle: %f\n", math.mx, math.my, game->map[math.my][math.mx], math.ra);
		}

		/* just to print */

		t_coord point_5;
		t_coord point_6;

		point_5.x = game->player->px;
		point_5.y = game->player->py;
		point_5.color = 0xFF0000FF;
		point_6.x = math.sx;
		point_6.y = math.sy;
		point_6.color = 0xFF0000FF;

		bresenham(&point_5, &point_6, game->pmlx_image);

		/* Draw 3D scene */

		draw_scene(&math, game, r);

		r += 1;
		math.ra += (0.15 * DR);
		norm_angle(&math.ra);
	}
}

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

void find_horiz_ray_dim(t_math *math, t_game *game)
{
	if (math->ra == 0 || math->ra == PI)
	{
		math->rx = game->player->px + game->width;
		math->ry = game->player->py + game->height;
	}
	else if (math->ra > PI) // looking up
	{
		math->ry = (((int)game->player->py >> BIT) << BIT) - 0.0001;
		math->rx = (game->player->py - math->ry) * math->aTan + game->player->px;
		math->yo = -CELL;
		math->xo = (-math->yo) * math->aTan;
	}
	else if (math->ra < PI) // looking down
	{
		math->ry = (((int)game->player->py >> BIT) << BIT) + CELL;
		math->rx = (game->player->py - math->ry) * math->aTan + game->player->px;
		math->yo = CELL;
		math->xo = (-math->yo) * math->aTan;
	}
}

void find_vert_ray_dim(t_math *math, t_game *game)
{
	if (math->ra == PI / 2 || math->ra == 3*PI/2)
	{
		math->rx = game->player->px + game->width;
		math->ry = game->player->py + game->height; 
	}
	else if (math->ra > PI / 2 && math->ra < 3 * PI / 2) // looking left
	{
		math->rx = (((int)game->player->px >> BIT) << BIT) - 0.0001;
		math->ry = (game->player->px - math->rx) * math->nTan + game->player->py;
		math->xo = -CELL;
		math->yo = (-math->xo) * math->nTan;
	}
	else if (math->ra < PI / 2 || math->ra > 3 * PI / 2) // looking right
	{
		math->rx = (((int)game->player->px >> BIT) << BIT) + CELL;
		math->ry = (game->player->px - math->rx) * math->nTan + game->player->py;
		math->xo = CELL;
		math->yo = (-math->xo) * math->nTan;
	}
}

void find_horiz_ray_limit(t_math *math, t_game *game)
{
	math->mx = abs((int)(math->rx) >> BIT);
	math->my = abs((int)(math->ry) >> BIT);

	while (math->mx < game->width && math->my < game->height && game->map[math->my][math->mx] == '0')
	{
		math->rx += math->xo;
		math->ry += math->yo;
		math->mx = abs((int)(math->rx) >> BIT);
		math->my = abs((int)(math->ry) >> BIT);
	}
	math->hx = math->rx;
	math->hy = math->ry;
	// printf("hx: %f, hy: %f, px: %f, py: %f\n", math->hx, math->hy, game->player->px, game->player->py);
	math->dist_horiz = dist(game->player->px, game->player->py, math->hx, math->hy);
}

void find_vert_ray_limit(t_math *math, t_game *game)
{
	math->mx = abs((int)(math->rx) >> BIT);
	math->my = abs((int)(math->ry) >> BIT);

	while (math->mx < game->width && math->my < game->height && game->map[math->my][math->mx] == '0')
	{

		math->rx += math->xo;
		math->ry += math->yo;
		math->mx = abs((int)(math->rx) >> BIT);
		math->my = abs((int)(math->ry) >> BIT);
	}
	math->vx = math->rx;
	math->vy = math->ry;
	math->dist_vert = dist(game->player->px, game->player->py, math->vx, math->vy);
}
