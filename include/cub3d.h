/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:12:59 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/05 18:25:35 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
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

typedef struct s_scene
{
	int			size;
	int			max_len;
	int			player;
	int			north;
	int			south;
	int			west;
	int			east;
	int			floor;
	int			ceiling;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	uint32_t	c_color;
	uint32_t	f_color;
	bool		scene_error;
}				t_scene;

typedef struct s_game
{
	char		**map;
	char		**scene;
	t_scene		*scene_data;
}				t_game;

/*-------------------PARSING AND VALIDATION----------------------------------*/
void			validate_input(int argc, char *argv, t_game *game);
void			read_scene(t_game *game, char *argv);
int				check_misconfiguration(t_game *game);
void			check_rgb(t_scene *scene_data, char *line, int *cardinal);
void			check_cardinal(t_scene *scene_data);
void			check_path(char *line, int *cardinal);
void			init_cardinals(t_scene *scene_data);
void			read_map(t_game *game, int row);
void			validate_map(t_game *game);
char			*fill_spaces(char *cur_line, t_game *game);
void			game_over(char *msg, t_game *game);
void			get_num_lines(char *argv, t_scene *scene_data);
void			check_format(char *argv);
void			check_characters(t_game *game, char *line);
void			check_boundaries(t_game *game, char *line, int row);

/*-------------------GAME OVER-----------------------------------------------*/
void			game_over(char *msg, t_game *game);
void			free_map(char **map);

/*-------------------UTILS---------------------------------------------------*/
bool			is_empty_line(char *line);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif