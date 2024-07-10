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
#define CUB3D_H

#include "libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "MLX42/MLX42.h"

#define WIDTH 1024
#define HEIGHT 512
#define CELL 16
#define PI 3.14159265359
# define DR 0.0174533

/*-------------------STRUCTS-------------------------------------------------*/

// coordinates define where a ray starts and where it intersects with objects
typedef struct s_coord
{
	double x;
	double y;
	uint32_t	color;
} t_coord;

// vectors define the direction and movement of the ray through the scene
typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player
{
	int mx;
	int my;
	int px;
	int py;
	char dir;
	double dirx;
	double diry;
	double pa;
	double pdx;
	double pdy;
} t_player;

typedef struct s_scene
{
	int size;
	int player_count;
	int north;
	int south;
	int west;
	int east;
	int floor;
	int ceiling;
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
	uint32_t c_color;
	uint32_t f_color;
} t_scene;

typedef struct s_game
{
	char **map;
	char **scene;
	t_scene *scene_data;
	t_player *player;
	size_t height;
	size_t width;
	mlx_t *mlx;
	mlx_image_t *mlx_image; // remove
	mlx_image_t *pmlx_image; // remove
	mlx_key_data_t *keydata;
	mlx_texture_t *no_text;
	mlx_texture_t *so_text;
	mlx_texture_t *we_text;
	mlx_texture_t *ea_text;
	mlx_image_t *no_img;
	mlx_image_t *so_img;
	mlx_image_t *we_img;
	mlx_image_t *ea_img;
	mlx_image_t *background;
} t_game;


typedef struct s_math
{
	double aTan;
	double nTan;
	double ra;
	double rx;
	double ry;
	double xo;
	double yo;
	double hx;
	double hy;
	double distH;
	double vx;
	double vy;
	double distV;
	double ca;
	int dof;
	int mx;
	int my;
} t_math;


/*-------------------PARSING AND VALIDATION----------------------------------*/
void parse_file(int argc, char *argv, t_game *game);
void read_scene(t_game *game, char *argv);
int check_misconfiguration(t_game *game);
void check_rgb(char *line, int *cardinal, uint32_t *color);
void check_data(t_game *game);
void check_path(char *line, int *cardinal, char **path);
void init_data(t_game *game);
void init_player(t_game *game, char **map);
void read_map(t_game *game, int row);
void validate_map(t_game *game);
char *fill_spaces(char *cur_line, t_game *game);
void get_num_lines(char *argv, t_scene *scene_data);
void check_format(char *argv);
void check_characters(char *line);
void check_boundaries(t_game *game, char *line, int row);
void init_pos(t_game *game);
mlx_t *init_mlx(void);
mlx_image_t *init_image(mlx_t *mlx);
void init_window(mlx_t *mlx, mlx_image_t *mlx_image);

/*-------------------RAYCASTING----------------------------------------------*/

/*-------------------HOOKS AND MOVES-----------------------------------------*/
void hook(mlx_key_data_t keydata, void *param);
void move_vertical(t_game *game, int direction);
void move_horizontal(t_game *game, int direction);
double fix_ang(double a);

/*-------------------LOAD TEXTURES AND PLACE IMAGES--------------------------*/
void load_images(t_game *game);
void render_background(t_game *game);

/*-------------------GAME OVER-----------------------------------------------*/
void game_over(char *msg);
void close_window(void *param);
void delete_images(t_game *game);

/*-------------------UTILS---------------------------------------------------*/
bool is_empty_line(char *line);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);


/*-------------------RENDER---------------------------------------------------*/
void	put_valid_pixel(mlx_image_t *mlx_image, int x, int y, uint32_t color);
void fill_cell(t_coord *point_1, t_coord *point_2, mlx_image_t *mlx_image);
void	render_map(t_game *game);
void get_distance(t_game *game);

//bresenham //remove

typedef struct s_bres
{
	int			dx;
	int			dy;
	int			abs_dx;
	int			abs_dy;
	int			p;
}				t_bres;

void	check_delta_to_move_variable(int d, int *variable);
void	slope_lower_1(t_bres *aux, t_coord *point, mlx_image_t *mlx_image);
void	slope_bigger_equal_1(t_bres *aux, t_coord *point, mlx_image_t *mlx_image);
void	bresenham(t_coord *point_1, t_coord *point_2, mlx_image_t *mlx_image);

#endif