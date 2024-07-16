#include "cub3d.h"

void	put_valid_pixel(mlx_image_t *mlx_image, int x, int y, uint32_t color)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(mlx_image, x, y, color);
}

uint32_t	texture_to_rgb(mlx_texture_t *texture, int x, int y)
{
	uint8_t	*rgb;

	/* c = T[(int)(ty*32) + (int)tx] */
	rgb = &texture->pixels[(y * texture->width + x) * texture->bytes_per_pixel];
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | rgb[3]);
}

mlx_texture_t	*get_wall(t_game *game, t_math *math)
{
	if (math->is_horiz)
	{
		if (math->ra > PI && math->ra < 2 * PI)
			return (game->no_text);
		else
			return (game->so_text);
	}
	else
	{
		if (math->ra < PI / 2 || math->ra > 3 * PI / 2)
			return (game->ea_text);
		else
			return (game->we_text);
	}
}

void	fill_cell(t_coord *point_1, t_coord *point_2, mlx_image_t *mlx_image)
{
	int			x;
	int			y;
	uint32_t	color;

	x = point_1->x;
	y = point_1->y;
	color = point_1->color;
	while (y <= point_2->y)
	{
		x = point_1->x;
		while (x <= point_2->x)
		{
			put_valid_pixel(mlx_image, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	size_t	i;
	size_t	j;
	t_coord	point_1;
	t_coord	point_2;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			point_1.x = CELL * j;
			point_1.y = CELL * i;
			point_2.x = (CELL * j) + (CELL - 1);
			point_2.y = (CELL * i) + (CELL - 1);
			if (game->map[i][j] == '1')
			{
				point_1.color = 0xffffffff;
				point_2.color = 0xffffffff;
			}
			else
			{
				point_1.color = 0x00000000;
				point_2.color = 0x00000000;
			}
			fill_cell(&point_1, &point_2, game->mlx_image);
			j++;
		}
		i++;
	}
}

void	draw_scene(t_math *math, t_game *game, int r)
{
	int			y;
	double		tx;
	double		ty;
	double		ty_step;
	uint32_t	color;
	t_coord		point_1;
	t_coord		point_2;

	math->ca = game->player->pa - math->ra;
	norm_angle(&math->ca);
	math->distS = cos(math->ca) * math->distS;
	math->lineH = (HEIGHT * CELL) / math->distS;
	math->lineO = (HEIGHT - math->lineH) / 2;
	/* Texture */
	ty_step = game->tex_height / math->lineH;
	ty = 0;
	if (math->is_horiz) // point in horizontal line
	{
		// printf("AQUI\n");
		tx = (int)(math->sx * (game->tex_width / CELL)) % game->tex_width;
		// if (math->ra < PI && math->ra > 0)
		// 	tx = (game->tex_width - 1) - tx;
	}
	else // point in vertical line
	{
		tx = (int)(math->sy * (game->tex_height / CELL)) % game->tex_height;
		// if (math->ra > (PI / 2) && math->ra < (3 * PI / 2))
		// 	tx = (game->tex_width - 1) - tx;
	}
	y = 0;
	while (y < math->lineH)
	{
		color = texture_to_rgb(get_wall(game, math), tx, ty);
		point_1.x = (r * 8) + 530;
		point_1.y = math->lineO + y;
		point_1.color = color;
		// point_2.x = (((r + 1) * 8) - 1) + 530;
		point_2.x = ((r + 1) * 8) + 530;
		point_2.y = math->lineO + y;
		point_2.color = color;
		bresenham(&point_1, &point_2, game->pmlx_image);
		ty += ty_step;
		y++;
	}
	// point_1.x = (r * 8) + 530;
	// point_1.y = math->lineO;
	// point_1.color = 0xFF0000FF;
	// point_2.x = (((r + 1) * 8) - 1) + 530;
	// point_2.y = math->lineO + math->lineH;
	// point_2.color = 0xFF0000FF;
	// fill_cell(&point_1, &point_2, game->pmlx_image);
}
