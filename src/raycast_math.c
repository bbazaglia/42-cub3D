/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:44:05 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 14:41:52 by cogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_and_update_raycast(t_raycast *raycast, t_game *game, int ray)
{
	initialize_raycast(raycast, &raycast->horiz_hit, &raycast->horiz_dist);
	raycast->tan = (-1) / tan(raycast->ray_angle);
	find_horiz_ray_pos(raycast, game);
	find_horiz_ray_limit(raycast, game);
	initialize_raycast(raycast, &raycast->vert_hit, &raycast->vert_dist);
	raycast->rev_tan = (-1) * tan(raycast->ray_angle);
	find_vert_ray_pos(raycast, game);
	find_vert_ray_limit(raycast, game);
	find_shortest_distance(raycast);
	print_ray(game, raycast);
	draw_wall(raycast, game, ray);
	raycast->ray_angle += (0.075 * CONV_DEG_TO_RAD);
	norm_angle(&raycast->ray_angle);
}

/*
looking up: raycast->ray_angle > PI
looking down: raycast->ray_angle < PI
*/
void	find_horiz_ray_pos(t_raycast *raycast, t_game *game)
{
	if (compare_angles(raycast->ray_angle, 0)
		|| compare_angles(raycast->ray_angle, PI)
		|| compare_angles(raycast->ray_angle, PI_360))
	{
		raycast->ray_pos.x = game->player->pos.x;
		raycast->ray_pos.y = game->player->pos.y;
	}
	else if (raycast->ray_angle > PI)
	{
		raycast->ray_pos.y = (((int)game->player->pos.y >> BIT) << BIT)
			- 0.0001;
		raycast->ray_pos.x = (game->player->pos.y - raycast->ray_pos.y)
			* raycast->tan + game->player->pos.x;
		raycast->step.y = -CELL;
		raycast->step.x = (-raycast->step.y) * raycast->tan;
	}
	else if (raycast->ray_angle < PI)
	{
		raycast->ray_pos.y = (((int)game->player->pos.y >> BIT) << BIT) + CELL;
		raycast->ray_pos.x = (game->player->pos.y - raycast->ray_pos.y)
			* raycast->tan + game->player->pos.x;
		raycast->step.y = CELL;
		raycast->step.x = (-raycast->step.y) * raycast->tan;
	}
}

/*
looking left: raycast->ray_angle > PI_90 && raycast->ray_angle < PI_270
looking right: raycast->ray_angle < PI_90 || raycast->ray_angle > PI_270
*/
void	find_vert_ray_pos(t_raycast *raycast, t_game *game)
{
	if (compare_angles(raycast->ray_angle, PI_90)
		|| compare_angles(raycast->ray_angle, PI_270))
	{
		raycast->ray_pos.x = game->player->pos.x;
		raycast->ray_pos.y = game->player->pos.y;
	}
	else if (raycast->ray_angle > PI_90 && raycast->ray_angle < PI_270)
	{
		raycast->ray_pos.x = (((int)game->player->pos.x >> BIT) << BIT)
			- 0.0001;
		raycast->ray_pos.y = (game->player->pos.x - raycast->ray_pos.x)
			* raycast->rev_tan + game->player->pos.y;
		raycast->step.x = -CELL;
		raycast->step.y = (-raycast->step.x) * raycast->rev_tan;
	}
	else if (raycast->ray_angle < PI_90 || raycast->ray_angle > PI_270)
	{
		raycast->ray_pos.x = (((int)game->player->pos.x >> BIT) << BIT) + CELL;
		raycast->ray_pos.y = (game->player->pos.x - raycast->ray_pos.x)
			* raycast->rev_tan + game->player->pos.y;
		raycast->step.x = CELL;
		raycast->step.y = (-raycast->step.x) * raycast->rev_tan;
	}
}

void	find_horiz_ray_limit(t_raycast *raycast, t_game *game)
{
	if (compare_angles(raycast->ray_angle, 0)
		|| compare_angles(raycast->ray_angle, PI)
		|| compare_angles(raycast->ray_angle, PI_360))
	{
		raycast->horiz_dist = HIGH_VALUE;
		return ;
	}
	raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
	raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);
	while (raycast->map_x < game->width && raycast->map_y < game->height
		&& game->map[raycast->map_y][raycast->map_x] == '0')
	{
		raycast->ray_pos.x += raycast->step.x;
		raycast->ray_pos.y += raycast->step.y;
		raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
		raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);
	}
	raycast->horiz_hit.x = raycast->ray_pos.x;
	raycast->horiz_hit.y = raycast->ray_pos.y;
	raycast->horiz_dist = dist(game->player->pos.x, game->player->pos.y,
			raycast->horiz_hit.x, raycast->horiz_hit.y);
}

void	find_vert_ray_limit(t_raycast *raycast, t_game *game)
{
	if (compare_angles(raycast->ray_angle, PI_90)
		|| compare_angles(raycast->ray_angle, PI_270))
	{
		raycast->vert_dist = HIGH_VALUE;
		return ;
	}
	raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
	raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);
	while (raycast->map_x < game->width && raycast->map_y < game->height
		&& game->map[raycast->map_y][raycast->map_x] == '0')
	{
		raycast->ray_pos.x += raycast->step.x;
		raycast->ray_pos.y += raycast->step.y;
		raycast->map_x = abs((int)(raycast->ray_pos.x) >> BIT);
		raycast->map_y = abs((int)(raycast->ray_pos.y) >> BIT);
	}
	raycast->vert_hit.x = raycast->ray_pos.x;
	raycast->vert_hit.y = raycast->ray_pos.y;
	raycast->vert_dist = dist(game->player->pos.x, game->player->pos.y,
			raycast->vert_hit.x, raycast->vert_hit.y);
}
