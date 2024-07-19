#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42/MLX42.h"
#include "libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 1300
#define HEIGHT 600
#define CELL 16
#define BIT 4
#define CONV_DEG_TO_RAD 0.0174533
#define HIGH_VALUE 1000000
#define PRECISION 1e-9
#define PI 3.141592653589793
#define PI_90 1.570796326794897
#define PI_270 4.712388980384690
#define PI_360 6.283185307179586

/*-------------------STRUCTS-------------------------------------------------*/

typedef enum e_mlx_action
{
	INIT,
	NEW_IMAGE,
	IMAGE_TO_WINDOW,
} t_mlx_action;

typedef struct s_coord
{
	double x;
	double y;
	uint32_t color;
} t_coord;

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player
{
	double angle;
	int map_x_coord;
	int map_y_coord;
	char facing_dir;
	t_vector dir_vector;
	t_vector pos;
	t_vector delta;
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
	uint32_t ceiling_color;
	uint32_t floor_color;
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
	mlx_image_t *mlx_image;
	mlx_image_t *player_image;
	mlx_key_data_t *keydata;
	mlx_texture_t *no_text;
	mlx_texture_t *so_text;
	mlx_texture_t *we_text;
	mlx_texture_t *ea_text;
	mlx_texture_t *texture;
	int tex_width;
	int tex_height;
} t_game;

typedef struct s_raycast
{
	double tan;
	double rev_tan;
	double ray_angle;
	t_vector ray_pos;
	t_vector step;
	t_vector horiz_hit;
	double horiz_dist;
	t_vector vert_hit;
	double vert_dist;
	size_t map_x;
	size_t map_y;
	double corrected_angle;
	t_vector shortest_hit;
	double shortest_dist;
	double line_height;
	double line_offset;
	bool is_horizontal;
} t_raycast;

typedef struct s_bres
{
	int dx;
	int dy;
	int abs_dx;
	int abs_dy;
	int p;
} t_bres;

/*-------------------VALIDATE MAP--------------------------------------------*/
void check_format(char *argv);
void validate_map(t_game *game);
void check_data(t_game *game);
int check_misconfiguration(t_game *game);
void check_player(t_game *game);

/*-------------------PARSING-------------------------------------------------*/
void parse_file(int argc, char *argv, t_game *game);
void read_scene(t_game *game, char *argv);
void init_data(t_game *game);
void init_player(t_game *game, char **map);
void read_map(t_game *game, int row);
char *fill_spaces(char *cur_line, t_game *game);
void get_num_lines(char *argv, t_scene *scene_data);
void init_pos(t_game *game);

/*-------------------HOOKS AND MOVES-----------------------------------------*/
void close_window(t_game *game);
void hook(mlx_key_data_t keydata, void *param);
void rotate_key_left(t_game *game);
void rotate_key_right(t_game *game);
bool check_collision(t_game *game, double x, double y);
void move_key_w(t_game *game);
void move_key_s(t_game *game);
void move_key_a(t_game *game);
void move_key_d(t_game *game);

/*-------------------LOAD TEXTURES AND PLACE IMAGES--------------------------*/
void load_images(t_game *game);

/*-------------------GAME OVER-----------------------------------------------*/
void game_over(char *msg);
void end_mlx(t_game *game);
void delete_images(t_game *game);

/*-------------------RENDER---------------------------------------------------*/
void draw_wall(t_raycast *raycast, t_game *game, int r);
void render_background(t_game *game);

/*-------------------BRESENHAM------------------------------------------------*/
void check_delta_to_move_variable(int d, int *variable);
void slope_lower_1(t_bres *aux, t_coord *point,
				   mlx_image_t *mlx_image);
void slope_bigger_equal_1(t_bres *aux, t_coord *point,
						  mlx_image_t *mlx_image);
void bresenham(t_coord *point_1, t_coord *point_2,
			   mlx_image_t *mlx_image);

/*-------------------RAYCAST-------------------------------------------------*/
void get_distance(t_game *game);
void find_shortest_distance(t_raycast *raycast);
void initialize_raycast(t_raycast *raycast, t_vector *vector,
						double *dist);
void norm_angle(double *angle);
double dist(int ax, int ay, int bx, int by);
void calculate_and_update_raycast(t_raycast *raycast,
								  t_game *game,
								  int ray);
void find_horiz_ray_pos(t_raycast *raycast, t_game *game);
void find_vert_ray_pos(t_raycast *raycast, t_game *game);
void find_horiz_ray_limit(t_raycast *raycast, t_game *game);
void find_vert_ray_limit(t_raycast *raycast, t_game *game);
bool compare_angles(double angle1, double angle2);

/*-------------------MINIMAP-------------------------------------------------*/
void draw_player_square(t_game *game);
void draw_player_direction(t_game *game);
void print_ray(t_game *game, t_raycast *raycast);
void render_minimap(t_game *game);

/*-------------------UTILS---------------------------------------------------*/
bool is_empty_line(char *line);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void fill_cell(t_coord *point_1, t_coord *point_2,
			   mlx_image_t *mlx_image);
void put_valid_pixel(mlx_image_t *mlx_image, int x, int y,
					 uint32_t color);
void safe_mlx_action(int action, t_game *game);

#endif