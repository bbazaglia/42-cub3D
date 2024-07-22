/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:37:43 by string            #+#    #+#             */
/*   Updated: 2024/07/22 09:21:14 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	compare_angles(double angle1, double angle2)
{
	if (fabs(angle1 - angle2) < PRECISION)
		return (true);
	return (false);
}
