/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:12:59 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/03 16:16:06 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*-------------------STRUCTS-------------------------------------------------*/

// coordinates define where a ray starts and where it intersects with objects
typedef struct s_coord
{
	double		x;
	double		y;
}				t_coord;

// vectors define the direction and movement of the ray through the scene
typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_map_data
{
	int			size;
	int			max_len;
	int			player;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	uint32_t	c_color;
	uint32_t	f_color;
}				t_map_data;

typedef struct s_game
{
	char		**map;
	t_map_data	*map_data;
}				t_game;

/*-------------------PARSING AND VALIDATION----------------------------------*/
void			validate_input(int argc, char *argv, t_game *game);
void			read_map(t_game *game, char *argv);
char			*fill_spaces(char *cur_line, t_game *game);
void			game_over(char *msg, t_game *game);
void			get_num_lines(char *argv, t_map_data *map_data);
void			check_format(char *argv);
void			check_characters(t_game *game, char *line);
void			check_boundaries(t_game *game, char *line, int row);

/*-------------------GAME OVER-----------------------------------------------*/
void			game_over(char *msg, t_game *game);
void			free_map(char **map);

#endif