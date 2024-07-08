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

void game_over(char *msg)
{
    int exit_code;

    exit_code = EXIT_SUCCESS;
    if (msg)
    {
        printf("%s\n", msg);
        exit_code = EXIT_FAILURE;
    }
    free_mem(get_mem_address());
	exit(exit_code);
}
