/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:12:59 by bbazagli          #+#    #+#             */
/*   Updated: 2024/07/16 11:35:31 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1024
# define HEIGHT 512
# define CELL 16
# define BIT 4
# define PI 3.14159265359
# define DR 0.0174533
# define HIGH_VALUE 1000000

/*-------------------STRUCTS-------------------------------------------------*/

// coordinates define where a ray starts and where it intersects with objects
typedef struct s_coord
{
	double			x;
	double			y;
	uint32_t		color;
}					t_coord;

// vectors define the direction and movement of the ray through the scene
// typedef struct s_vector
// {
// 	double x;
// 	double y;
// } t_vector;

typedef struct s_player
{
	int				mx;
	int				my;
	double			px;
	double			py;
	char			dir;
	double			dirx;
	double			diry;
	double			pa;
	double			pdx;
	double			pdy;
}					t_player;

typedef struct s_scene
{
	int				size;
	int				player_count;
	int				north;
	int				south;
	int				west;
	int				east;
	int				floor;
	int				ceiling;
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	uint32_t		c_color;
	uint32_t		f_color;
}					t_scene;

typedef struct s_game
{
	char			**map;
	char			**scene;
	t_scene			*scene_data;
	t_player		*player;
	size_t			height;
	size_t			width;
	mlx_t			*mlx;
	mlx_image_t		*mlx_image;
	mlx_image_t		*pmlx_image; // remove
	mlx_key_data_t	*keydata;
	mlx_texture_t	*no_text;
	mlx_texture_t	*so_text;
	mlx_texture_t	*we_text;
	mlx_texture_t	*ea_text;
	mlx_texture_t	*texture;
	int				tex_width;
	int				tex_height;
}					t_game;

typedef struct s_math
{
	double			aTan;
	double			nTan;
	double			ra;
	double			rx;
	double			ry;
	double			xo;
	double			yo;
	double			hx;
	double			hy;
	double			distH;
	double			vx;
	double			vy;
	double			distV;
	size_t			mx;
	size_t			my;
	double			ca;
	double			sx;
	double			sy;
	double			distS;
	double			lineH;
	double			lineO;
	bool			is_horiz;
}					t_math;

typedef struct s_bres
{
	int				dx;
	int				dy;
	int				abs_dx;
	int				abs_dy;
	int				p;
}					t_bres;

/*-------------------PARSING AND VALIDATION----------------------------------*/
void				parse_file(int argc, char *argv, t_game *game);
void				read_scene(t_game *game, char *argv);
int					check_misconfiguration(t_game *game);
void				check_rgb(char *line, int *cardinal, uint32_t *color);
void				check_data(t_game *game);
void				check_path(char *line, int *cardinal, char **path);
void				init_data(t_game *game);
void				init_player(t_game *game, char **map);
void				read_map(t_game *game, int row);
void				validate_map(t_game *game);
char				*fill_spaces(char *cur_line, t_game *game);
void				get_num_lines(char *argv, t_scene *scene_data);
void				check_format(char *argv);
void				check_characters(char *line);
void				check_boundaries(t_game *game, char *line, int row);
void				init_pos(t_game *game);
mlx_t				*init_mlx(void);
mlx_image_t			*init_image(mlx_t *mlx);
void				init_window(mlx_t *mlx, mlx_image_t *mlx_image);

/*-------------------RAYCASTING----------------------------------------------*/

/*-------------------HOOKS AND MOVES-----------------------------------------*/
void				hook(mlx_key_data_t keydata, void *param);
void				move_vertical(t_game *game, int direction);
void				move_horizontal(t_game *game, int direction);
double				fix_ang(double a);

bool				check_collision(t_game *game, char key);

/*-------------------LOAD TEXTURES AND PLACE IMAGES--------------------------*/
void				load_images(t_game *game);
void				render_background(t_game *game);

/*-------------------GAME OVER-----------------------------------------------*/
void				game_over(char *msg);
void				end_mlx(t_game *game);
void				delete_images(t_game *game);

/*-------------------UTILS---------------------------------------------------*/
bool				is_empty_line(char *line);
int32_t				ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

/*-------------------RENDER---------------------------------------------------*/
void				put_valid_pixel(mlx_image_t *mlx_image, int x, int y,
						uint32_t color);
void				fill_cell(t_coord *point_1, t_coord *point_2,
						mlx_image_t *mlx_image);
void				render_map(t_game *game);
void				draw_scene(t_math *math, t_game *game, int r);
uint32_t			texture_to_rgb(mlx_texture_t *texture, int x, int y);
mlx_texture_t		*get_wall(t_game *game, t_math *math);

//bresenham

void				check_delta_to_move_variable(int d, int *variable);
void				slope_lower_1(t_bres *aux, t_coord *point,
						mlx_image_t *mlx_image);
void				slope_bigger_equal_1(t_bres *aux, t_coord *point,
						mlx_image_t *mlx_image);
void				bresenham(t_coord *point_1, t_coord *point_2,
						mlx_image_t *mlx_image);

/*-------------------MATH---------------------------------------------------*/
void				get_distance(t_game *game);
void				norm_angle(double *angle);
double				dist(int ax, int ay, int bx, int by);
void				find_horiz_ray_dim(t_math *math, t_game *game);
void				find_vert_ray_dim(t_math *math, t_game *game);
void				find_horiz_ray_limit(t_math *math, t_game *game);
void				find_vert_ray_limit(t_math *math, t_game *game);

#endif