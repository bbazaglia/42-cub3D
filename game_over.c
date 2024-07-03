/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:37:31 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/03 15:28:00 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void game_over(char *msg, t_game *game)
{
    int exit_code;

    exit_code = EXIT_SUCCESS;
    if (msg)
    {
        printf(msg);
        exit_code = EXIT_FAILURE;
    }
	if (game->map)
		free_map(game->map);
    
	// add other elements to free
    
	exit(exit_code);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	if (map)
	{
		free(map);
		map = NULL;
	}
}
