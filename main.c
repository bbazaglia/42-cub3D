/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:59:50 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 10:33:48 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// to do: correct parsing, the file will contain more scene_data than just the map

int main(int argc, char **argv)
{
    validate_input(argc, argv[1], game);
}