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
# include <stdint.h>
# include <stdio.h>
# include "MLX42/MLX42.h"

# define WIDTH 1024
# define HEIGHT 512
# define CELL 64
# define PI 3.14159265359


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

typedef struct s_player
{
	int			mx;
	int			my;
	int			px;
	int			py;
	char 		dir;
	double		dirx;
	double		diry;
	double		pa;
}				t_player;

typedef struct s_scene
{
	int			size;
	int			player_count;
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
}				t_scene;

typedef struct s_game
{
	char			**map;
	char			**scene;
	t_scene			*scene_data;
	t_player		*player;
	size_t			height;
	size_t			width;
	mlx_t			*mlx;
	mlx_key_data_t	*keydata;
	mlx_texture_t	*no_text;
	mlx_texture_t	*so_text;
	mlx_texture_t	*we_text;
	mlx_texture_t	*ea_text;
	mlx_image_t		*no_img;
	mlx_image_t		*so_img;
	mlx_image_t		*we_img;
	mlx_image_t		*ea_img;
	mlx_image_t		*background;
}				t_game;

/*-------------------PARSING AND VALIDATION----------------------------------*/
void			parse_file(int argc, char *argv, t_game *game);
void			read_scene(t_game *game, char *argv);
int				check_misconfiguration(t_game *game);
void			check_rgb(char *line, int *cardinal, uint32_t *color);
void			check_data(t_game *game);
void			check_path(char *line, int *cardinal, char **path);
void			init_data(t_game *game);
void    		init_player(t_game *game, char **map);
void			read_map(t_game *game, int row);
void			validate_map(t_game *game);
char			*fill_spaces(char *cur_line, t_game *game);
void			get_num_lines(char *argv, t_scene *scene_data);
void			check_format(char *argv);
void			check_characters(char *line);
void			check_boundaries(t_game *game, char *line, int row);
void 			init_pos(t_game *game);

/*-------------------RAYCASTING----------------------------------------------*/

/*-------------------HOOKS---------------------------------------------------*/

/*-------------------LOAD TEXTURES AND PLACE IMAGES--------------------------*/
void			load_images(t_game *game);
void 			render_background(t_game *game);

/*-------------------GAME OVER-----------------------------------------------*/
void			game_over(char *msg);
void 			close_window(void *param);
void 			delete_images(t_game *game);

/*-------------------UTILS---------------------------------------------------*/
bool			is_empty_line(char *line);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);


#endif