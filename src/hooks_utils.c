
#include "cub3d.h"

bool check_collision(t_game *game, double x, double y)
{
	size_t mx;
	size_t my;

	mx = abs((int)(x) >> BIT);
	my = abs((int)(y) >> BIT);
	if (mx < game->width && my < game->height && game->map[my][mx] == '0')
		return (false);
	return (true);
}

void move_key_w(t_game *game)
{
	double x;
	double y;
	bool collision;

	x = game->player->pos.x + game->player->delta.x;
	y = game->player->pos.y + game->player->delta.y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		if (!game->player->delta.y)
			game->player->delta.y = 1.;
		game->player->pos.x += game->player->delta.x;
		game->player->pos.y += game->player->delta.y;
	}
}

void move_key_s(t_game *game)
{
	double x;
	double y;
	bool collision;

	x = game->player->pos.x - game->player->delta.x;
	y = game->player->pos.y - game->player->delta.y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		if (!game->player->delta.y)
			game->player->delta.y = 1.;
		game->player->pos.x -= game->player->delta.x;
		game->player->pos.y -= game->player->delta.y;
	}
}

void move_key_a(t_game *game)
{
	double x;
	double y;
	bool collision;

	x = game->player->pos.x - 1.5;
	y = game->player->pos.y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		game->player->pos.x -= 1.5;
	}
}

void move_key_d(t_game *game)
{
	double x;
	double y;
	bool collision;

	x = game->player->pos.x + 1.5;
	y = game->player->pos.y;
	collision = check_collision(game, x, y);
	if (!collision)
	{
		game->player->pos.x += 1.5;
	}
}
