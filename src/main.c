/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cogata <cogata@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/23 09:33:30 by cogata           ###   ########.fr       */
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
	raycast(&game);
	safe_mlx_action(IMAGE_TO_WINDOW, &game);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	end_mlx(&game);
	game_over("BYE!");
	return (EXIT_SUCCESS);
}
