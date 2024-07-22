/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/22 09:43:28 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	parse_file(argc, argv[1], &game);
	safe_mlx_action(INIT, &game);
	safe_mlx_action(NEW_IMAGE, &game);
	load_images(&game);
	render_minimap(&game);
	get_distance(&game);
	safe_mlx_action(IMAGE_TO_WINDOW, &game);
	mlx_key_hook(game.mlx, hook, &game);
	mlx_loop(game.mlx);
	end_mlx(&game);
	game_over("END");
	return (EXIT_SUCCESS);
}
