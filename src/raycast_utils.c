/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:37:43 by string            #+#    #+#             */
/*   Updated: 2024/07/19 12:39:50 by string           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool compare_angles(double angle1, double angle2) 
{
    if (fabs(angle1 - angle2) < PRECISION) 
		return (true);
	return (false);
}
