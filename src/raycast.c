/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:41:00 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/19 16:30:21 by string           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_distance(t_game *game)
{
	t_raycast	raycast;
	int			ray;
	
	draw_player_square(game);
	draw_player_direction(game);
	render_background(game);
	raycast.ray_angle = game->player->angle - (CONV_DEG_TO_RAD * 30);
	norm_angle(&raycast.ray_angle);
	ray = 0;
	while (ray < 800)
	{
		calculate_and_update_raycast(&raycast, game, ray);
		ray++;
	}
}

void	find_shortest_distance(t_raycast *raycast)
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

void	initialize_raycast(t_raycast *raycast, t_vector *vector, double *dist)
{
	raycast->ray_pos.x = 0;
	raycast->ray_pos.y = 0;
	vector->x = 0;
	vector->y = 0;
	*dist = HIGH_VALUE;
	raycast->map_x = 0;
	raycast->map_y = 0;
}

void	norm_angle(double *angle)
{
	if (*angle < 0)
		*angle += PI_360;
	if (*angle > PI_360)
		*angle -= PI_360;
}

double	dist(int ax, int ay, int bx, int by)
{
	double	result;

	result = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	if (isnan(result))
		result = HIGH_VALUE;
	return (result);
}
