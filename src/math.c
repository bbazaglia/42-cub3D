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
	
	int r;
	t_math math;

	math.ra = game->player->pa - (DR * 30);
	norm_angle(&math.ra);

	r = 0;
	while (r < 60)
	{

		/* HORIZONTAL LINES */

		math.aTan = (-1) / tan(math.ra);
		math.rx = 0;
		math.ry = 0;
		math.hx = 0;
		math.hy = 0;
		math.distH = HIGH_VALUE;
		math.mx = 0;
		math.my = 0;

		find_horiz_ray_dim(&math, game);
		find_horiz_ray_limit(&math, game);

		/* VERTICAL LINES */

		math.nTan = (-1) * tan(math.ra);
		math.rx = 0;
		math.ry = 0;
		math.vx = 0;
		math.vy = 0;
		math.distV = HIGH_VALUE;
		math.mx = 0;
		math.my = 0;

		find_vert_ray_dim(&math, game);
		find_vert_ray_limit(&math, game);

		/* find_shortest_distance */

		math.sx = math.hx;
		math.sy = math.hy;
		math.distS = math.distH;

		if (math.distH > math.distV)
		{
			math.sx = math.vx;
			math.sy = math.vy;
			math.distS = math.distV;
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
		math.ra += (1 * DR);
		norm_angle(&math.ra);
	}
}

void norm_angle(double *angle)
{
	if(*angle < 0)
		*angle += (2*PI);
	if(*angle > (2*PI))
		*angle -= (2*PI);
}

double dist(int ax, int ay, int bx, int by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void find_horiz_ray_dim(t_math *math, t_game *game)
{
	if (math->ra == 0 || math->ra == PI)
	{
		math->rx = game->player->px;
		math->ry = game->player->py;
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
	if (math->ra == 0 || math->ra == PI)
	{
		math->rx = game->player->px;
		math->ry = game->player->py;
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
	int dof;

	dof = 0;
	while (dof < 16) // replace this for collision verification
	{
		math->mx = abs((int)(math->rx) >> BIT);
		math->my = abs((int)(math->ry) >> BIT);
		if (math->mx < game->width && math->my < game->height && game->map[math->my][math->mx] == '1')
		{
			dof = 16;
			math->hx = math->rx;
			math->hy = math->ry;
			math->distH = dist(game->player->px, game->player->py, math->hx, math->hy);
		}
		else
		{
			math->rx += math->xo;
			math->ry += math->yo;
			dof += 1;
		}
	}
}

void find_vert_ray_limit(t_math *math, t_game *game)
{
	int dof;

	dof = 0;
	while (dof < 16) // replace this for collision verification
	{
		math->mx = abs((int)(math->rx) >> BIT);
		math->my = abs((int)(math->ry) >> BIT);
		if (math->mx < game->width && math->my < game->height && game->map[math->my][math->mx] == '1')
		{
			dof = 16;
			math->vx = math->rx;
			math->vy = math->ry;
			math->distV = dist(game->player->px, game->player->py, math->vx, math->vy);
		}
		else
		{
			math->rx += math->xo;
			math->ry += math->yo;
			dof += 1;
		}
	}
}

void draw_scene(t_math *math, t_game *game, int r)
{
	t_coord point_1;
	t_coord point_2;

	math->ca = game->player->pa - math->ra;
	norm_angle(&math->ca);

	math->distS = cos(math->ca) * math->distS;
	math->lineH = (HEIGHT * CELL) / math->distS;
	math->lineO = (HEIGHT - math->lineH)/2;

	point_1.x = (r * 8) + 530; 
	point_1.y = math->lineO;
	point_1.color = 0xFF0000FF;
	point_2.x = (((r + 1) * 8) - 1) + 530;
	point_2.y = math->lineO + math->lineH;
	point_2.color = 0xFF0000FF;

	fill_cell(&point_1, &point_2, game->pmlx_image);
}